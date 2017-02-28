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
#include <Model/LobbyStatePayload.hpp>


class MenuStateUpdateMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::LOBBY_STATE_CHANGE;

private:
    LobbyStatePayload _state;

public:

    MenuStateUpdateMessage() : _state() { }
    MenuStateUpdateMessage(const LobbyStatePayload &state) : _state(state) {}

    LobbyStatePayload &getState() {
        return _state;
    }
};

#endif //R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP
