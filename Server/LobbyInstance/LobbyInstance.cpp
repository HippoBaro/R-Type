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
    //Le premier qui fait un commentaire sur cette fonction aura le droit de la refaire xD
    std::string _textToSend = "Waiting\n";
    for (auto const &player : _players) {
        _textToSend += "Player ";
        _textToSend += (player.second->GetId() + 48);
        if (player.second->IsReady())
            _textToSend += "\tReady";
        else if (!player.second->IsReady())
            _textToSend += "\tNot Ready";
        _textToSend += "\n";
    }

    auto packer = RType::Packer(RType::WRITE);
    packer.Pack(_textToSend);

    for (auto const &cli : _clients)
        _eventManager->Emit(SendTCPNetworkPayloadMessage::EventType, new SendTCPNetworkPayloadMessage(packer, cli.second), this);
}