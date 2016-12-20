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
    uint16_t _id = 0;
    std::string _roomName = "toto";
    std::vector<PlayerRef> _players = std::vector<PlayerRef>();
    RType::EventManager _eventManager = RType::EventManager();

public:
    LobbyInstance();
};


#endif //R_TYPE_LOBBYINSTANCE_HPP
