//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_USERINPUTMESSAGE_HPP
#define R_TYPE_USERINPUTMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>

enum UserEventType {
    CLOSE_WINDOWS,
    USER_UP,
    USER_DOWN,
    USER_RIGHT,
    USER_LEFT,
    USER_SPACE,
    USER_ENTER,
    USER_ESCAPE
};

class UserInputMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    const UserEventType _event;

public:
    UserInputMessage(const UserEventType &event) : _event(event) {}

    const UserEventType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP
