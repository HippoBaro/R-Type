//
// Created by pasteu_e on 11/12/16.
//

#ifndef R_TYPE_MENULOBBYMESSAGE_HPP
#define R_TYPE_MENULOBBYMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>

enum LobbyEventType {
    USER_WAITING,
    USER_STOP_WAITING
};

class MenuLobbyMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::MENU_LOBBY;

private:
    const LobbyEventType _event;
    std::string _channelName = "";

public:
    MenuLobbyMessage(const LobbyEventType &event) : _event(event) {}

    MenuLobbyMessage(const LobbyEventType &event, const std::string &channelName) : _event(event) {
        _channelName = channelName;
    }

    const std::string &getChannelName() const {
        return _channelName;
    }

    const LobbyEventType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_MENULOBBYMESSAGE_HPP
