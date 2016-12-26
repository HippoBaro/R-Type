//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"

void LobbyManager::Start() {
    auto sub = RType::EventListener(_eventManager);
    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        _clients[_i++] = message->getClient();
    });
    sub.Subscribe<void, ReceivedTCPNetworkPayloadMessage>(ReceivedTCPNetworkPayloadMessage::EventType, [&](void *sender, ReceivedTCPNetworkPayloadMessage *message) {
        std::string data = std::string(message->getPayload()->Payload);
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
            _instances[roomName]->SetReady(message->getId(), true);
        } else if ()
    });
    Run();
}

void LobbyManager::Run() {
    while (true) {
        _networkManager.IsThereNewClient();
        _networkManager.CheckForIncomingMessage(_clients);
    }
}

bool LobbyManager::CreateInstance(std::string roomName) {
    if (_instances.find(roomName) == _instances.end()) {
        auto lobby = std::make_shared<LobbyInstance>(roomName);
        _instances[roomName] = lobby;
        return true;
    }
    return false;
}

bool LobbyManager::JoinInstance(std::string roomName, std::shared_ptr<PlayerRef> ref) {
    if (_instances.find(roomName) != _instances.end()) {
        return _instances[roomName]->AddPlayerToInstance(ref->GetId(), ref);
    }
    return false;
}
