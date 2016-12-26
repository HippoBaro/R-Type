//
// Created by pasteu_e on 17/12/16.
//

#include <iostream>
#include "LobbyInstance/LobbyInstance.hpp"

LobbyInstance::LobbyInstance(const std::shared_ptr<RType::EventManager> &eventManager, std::string roomName) : _roomName(roomName), _eventManager(eventManager) {

}

bool LobbyInstance::AddPlayerToInstance(uint8_t id, std::shared_ptr<PlayerRef> &ref) {
    if (_players.size() < 4) {
        _players[id] = ref;
        return true;
    }
    return false;
}

void LobbyInstance::SetReady(uint8_t id, bool ready) {
    _players[id]->SetReady(ready);
}

void LobbyInstance::PlayerLeft(uint8_t id) {
    if (_players.find(id) != _players.end()) {
        _players.erase(id);
    }
}

bool LobbyInstance::IsReady() {
    for(auto const& player : _players) {
        if (!player.second->IsReady())
            return false;
    }
    return true;
}

bool LobbyInstance::IsThereAnyone() {
    return _players.size() != 0;
}
