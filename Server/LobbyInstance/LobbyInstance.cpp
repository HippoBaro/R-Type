//
// Created by pasteu_e on 17/12/16.
//

#include <iostream>
#include <Messages/SendTCPNetworkPayloadMessage.hpp>
#include "LobbyInstance/LobbyInstance.hpp"

LobbyInstance::LobbyInstance(const std::shared_ptr<RType::EventManager> &eventManager, std::string roomName) : _roomName(roomName), _eventManager(eventManager) {

}

bool LobbyInstance::AddPlayerToInstance(uint8_t id, std::shared_ptr<IRTypeSocket> &client, std::shared_ptr<PlayerRef> &ref) {
    if (_players.size() < 4) {
        _clients[id] = client;
        _players[id] = ref;
        NotifyClients();
        return true;
    }
    return false;
}

void LobbyInstance::SetReady(uint8_t id, bool ready) {
    if (_players.find(id) != _players.end()) {
        _players[id]->SetReady(ready);
        NotifyClients();
    }
}

void LobbyInstance::PlayerLeft(uint8_t id) {
    if (_players.find(id) != _players.end()) {
        _clients.erase(id);
        _players.erase(id);
        NotifyClients();
    }
}

bool LobbyInstance::IsReady() {
    for (auto const &player : _players) {
        if (!player.second->IsReady())
            return false;
    }
    return true;
}

bool LobbyInstance::IsThereAnyone() {
    return _players.size() != 0;
}

void LobbyInstance::NotifyClients() {
    for (auto const &cli : _clients)
        _eventManager->Emit(SendTCPNetworkPayloadMessage::EventType, new SendTCPNetworkPayloadMessage(Serialize(_players[cli.first]), cli.second), this);
}

RType::Packer LobbyInstance::Serialize(std::shared_ptr<PlayerRef> &player) {
    auto packer = RType::Packer(RType::WRITE);
    auto tmp1 = player->GetId();
    auto tmp2 = player->IsReady();
    packer.Pack(tmp1);
    packer.Pack(tmp2);
    return packer;
}
