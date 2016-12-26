//
// Created by pasteu_e on 17/12/16.
//

#ifndef R_TYPE_LOBBYINSTANCE_HPP
#define R_TYPE_LOBBYINSTANCE_HPP

#include <EventDispatcher/EventManager.hpp>
#include <chrono>
#include <Entities/PlayerRef.hpp>

class LobbyInstance {
private:
    std::string _roomName;
    std::map<uint8_t, std::shared_ptr<PlayerRef>> _players = std::map<uint8_t, std::shared_ptr<PlayerRef>>();
    RType::EventManager _eventManager = RType::EventManager();

public:
    LobbyInstance(std::string roomName);
    bool AddPlayerToInstance(uint8_t id, std::shared_ptr<PlayerRef> ref);
    void SetReady(uint8_t id, bool ready);
    void PlayerLeft(uint8_t id);
    bool IsReady();
    bool IsThereAnyone();
};


#endif //R_TYPE_LOBBYINSTANCE_HPP
