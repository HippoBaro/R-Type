//
// Created by Etienne Pasteur on 27/12/2016.
//

#ifndef R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP
#define R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <EventDispatcher/Events.h>
#include <Entities/PlayerRef.hpp>
#include <vector>


class MenuStateUpdateMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::LOBBY_STATE_CHANGE;

private:
    std::vector<PlayerRef> _players = std::vector<PlayerRef>();

public:
    MenuStateUpdateMessage(const std::vector<PlayerRef> &players) : _players(players) {}

    const std::vector<PlayerRef> &GetPlayers() const {
        return _players;
    }

};

#endif //R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP
