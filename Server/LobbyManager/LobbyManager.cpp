//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"
#include <Messages/SendTCPNetworkPayloadMessage.hpp>
#include <Messages/ClientWaitForServerMessage.hpp>

LobbyManager::LobbyManager(std::shared_ptr<RType::EventManager> eventManager, std::shared_ptr<NetworkManager> networkManager) :
    _eventManager(eventManager),
    _networkManager(networkManager)
{}

void LobbyManager::Start() {
    std::cout << "LobbyManager Launched" << std::endl;

    RType::EventListener sub(_eventManager);

    //Event listener pour ajouter des clients a la pool
    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        std::cout << "New client connection" << std::endl;
        _clients[_nextClientId++] = message->getClient();
    });

    //Event listener pour ajouter des messages a envoyer sur le reseau
    sub.Subscribe<void, SendTCPNetworkPayloadMessage>(SendTCPNetworkPayloadMessage::EventType, [&](void *sender, SendTCPNetworkPayloadMessage *message) {
        _toSend.push_back(std::make_pair(message->getDestination(), message->ConvertToSocketMessage()));
    });

    //Event listener pour prendre des actions en fonctions de ce qui arrive du reseau
    sub.Subscribe<void, ReceivedTCPNetworkPayloadMessage>(ReceivedTCPNetworkPayloadMessage::EventType, [&](void *sender, ReceivedTCPNetworkPayloadMessage *message) {
        auto clientMessage = new ClientWaitForServerMessage();
        RType::Packer unpacker(RType::READ, message->getPayload()->Payload);
        clientMessage->Serialize(unpacker);
        if (clientMessage->getEventType() == USER_CREATE) {
            if (CreateInstance(clientMessage->getChannelName())) {
                auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
                JoinInstance(clientMessage->getChannelName(), player);
            }
        } else if (clientMessage->getEventType() == USER_JOIN) {
            auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
            JoinInstance(clientMessage->getChannelName(), player);
        } else if (clientMessage->getEventType() == USER_READY) {
            if (_instances.count(clientMessage->getChannelName()) > 0)
                _instances[clientMessage->getChannelName()]->SetReady(message->getId(), true);
        } else if (clientMessage->getEventType() == USER_QUIT)
            LeftInstance(clientMessage->getChannelName(), message->getId());
        else if (clientMessage->getEventType() == USER_DISCONNECT)
            UserDisconnect(message->getId());
    });
    Run();
}

void LobbyManager::Run() {
    while (true) {
        _networkManager->IsThereNewClient();
        _networkManager->CheckForIncomingMessage(_clients);
        CheckInstance();
        SendToClients();
    }
}

bool LobbyManager::CreateInstance(const std::string &roomName) {
    if (_instances.find(roomName) == _instances.end()) {
        auto lobby = std::make_shared<LobbyInstance>(_eventManager, roomName);
        _instances[roomName] = lobby;
        return true;
    }
    return false;
}

bool LobbyManager::JoinInstance(const std::string &roomName, const std::shared_ptr<PlayerRef> &ref) {
    if (_instances.find(roomName) != _instances.end()) {
        return _instances[roomName]->AddPlayerToInstance(ref->GetId(), _clients[ref->GetId()], ref);
    }
    return false;
}

void LobbyManager::LeftInstance(const std::string &roomName, const uint8_t id) {
    if (_instances.find(roomName) != _instances.end()) {
        _instances[roomName]->PlayerLeft(id);
    }
}

void LobbyManager::CheckInstance() {
    for (auto instance = _instances.begin() ; instance != _instances.end() ; ++instance) {
        if (!instance->second->IsThereAnyone()) {
            _instances.erase(instance->first);
            break;
        }
        if (instance->second->IsReady()) {
            //TODO: Transform LobbyInstance into GameInstance and remove LobbyInstance and close clients TCP connections
            std::cout << "Instance: " << instance->second->getRoomName() << " is ready to go !" << std::endl;

            TransformIntoGameInstance(instance);
        }
    }
}

void LobbyManager::SendToClients() {
    if (_toSend.size() != 0) {
        for (auto it = _toSend.begin(); it != _toSend.end();) {
            if (_networkManager->SendOverTCP(it->second, it->first, 100)) {
                it = _toSend.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void LobbyManager::UserDisconnect(uint8_t id) {
    for (auto const &instance : _instances) {
        if (instance.second->HaveYouSeenThisPlayer(id)) {
            LeftInstance(instance.second->getRoomName(), id);
            break;
        }
    }
    _clients.erase(id);
}

void LobbyManager::TransformIntoGameInstance(std::map<std::string, std::shared_ptr<LobbyInstance>>::iterator &instance)
{
    // Build Message
    std::string randomPartition("testPartition");
    std::vector<std::shared_ptr<PlayerRef>> playerRefs;
    for (auto it = instance->second->getPlayerRefs().begin(); it != instance->second->getPlayerRefs().end(); ++it)
        playerRefs.push_back(it->second);
    this->_eventManager->Emit(RType::Event::START_NEW_GAME, nullptr, new StartNewGameMessage(randomPartition, playerRefs));


    // Remove IRTypeSockets
    std::vector<uint8_t> ids;
    for (auto&& it : instance->second->getPlayerRefs())
        ids.push_back(it.first);

    for (auto it = _clients.begin() ; it != _clients.end() ; ++it)
        if (std::find(std::begin(ids), std::end(ids), it->first) != std::end(ids))
            _clients.erase(it);

    // Delete instance
    _instances.erase(instance);
}
