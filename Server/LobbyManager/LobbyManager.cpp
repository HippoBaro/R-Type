//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"
#include <Messages/SendTCPNetworkPayloadMessage.hpp>
#include <Messages/ClientWaitForServerMessage.hpp>

void LobbyManager::Start() {
    auto sub = RType::EventListener(_eventManager);

    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        _clients[_nextClientId++] = message->getClient();
    });
    sub.Subscribe<void, SendTCPNetworkPayloadMessage>(SendTCPNetworkPayloadMessage::EventType, [&](void *sender, SendTCPNetworkPayloadMessage *message) {
        //Je sait pas pourquoi mais si je depack pas ici dans le network manager message->getPacker().getBuffer() pointera sur \0
        //TODO: Ne pas dépack le message pour l'envoyer
/*
        auto depacker = RType::Packer(RType::READ, message->getPacker().getBuffer());
        std::string toSend;
        depacker.Pack(toSend);
        RTypeNetworkPayload payload(strdup(toSend.c_str()), (int) toSend.size());
*/
        _toSend.push_back(std::make_pair(message->getDestination(), message->ConvertToSocketMessage()));
    });
    sub.Subscribe<void, ReceivedTCPNetworkPayloadMessage>(ReceivedTCPNetworkPayloadMessage::EventType, [&](void *sender, ReceivedTCPNetworkPayloadMessage *message) {
        std::string data = std::string(message->getPayload()->Payload);

        auto payload = new ClientWaitForServerMessage();
        RType::Packer packer(RType::READ, message->getPayload()->Payload);
        payload->Serialize(packer);

        if (payload->getEventType() == USER_CREATE) {
            if (CreateInstance(payload->getChannelName())) {
                auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
                JoinInstance(payload->getChannelName(), player);
            }
        }
        else if (payload->getEventType() == USER_JOIN) {
            auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
            JoinInstance(payload->getChannelName(), player);
        }
        else if (payload->getEventType() == USER_READY) {
            if (_instances.count(payload->getChannelName()) > 0)
                _instances[payload->getChannelName()]->SetReady(message->getId(), true);
        }
        else if (payload->getEventType() == USER_QUIT)
            LeftInstance(payload->getChannelName(), message->getId());

/*        //TODO: Dépacker le payload

        if (data.find("[CREATE]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            if (CreateInstance(roomName)) {
                auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
                JoinInstance(roomName, player);
            }
        } else if (data.find("[JOIN]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
            JoinInstance(roomName, player);
        } else if (data.find("[READY]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            if (_instances.find(roomName) != _instances.end()) {
                _instances[roomName]->SetReady(message->getId(), true);
            }
        } else if (data.find("[QUIT]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            LeftInstance(roomName, message->getId());
        }*/
    });
    Run();
}

void LobbyManager::Run() {
    while (true) {
        _networkManager.IsThereNewClient();
        _networkManager.CheckForIncomingMessage(_clients);
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
    for (auto const &instance : _instances) {
        if (!instance.second->IsThereAnyone()) {
            _instances.erase(instance.first);
            break;
        }
        if (instance.second->IsReady()) {
            //TODO: Transform LobbyInstance into GameInstance and remove LobbyInstance and close clients TCP connections
        }
    }
}

void LobbyManager::SendToClients() {
    if (_toSend.size() != 0) {
        for (auto it = _toSend.begin(); it != _toSend.end();) {
            if (_networkManager.SendOverTCP(it->second, it->first, 100)) {
                it = _toSend.erase(it);
            } else {
                ++it;
            }
        }
    }
}