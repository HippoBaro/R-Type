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
    USER_UP,
    USER_DOWN,
    USER_RIGHT,
    USER_LEFT,
    USER_SPACE,
    USER_ENTER,
    USER_ESCAPE,
    USER_LETTER,
    CLOSE_WINDOWS
};

class UserInputMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    const UserEventType _event;
    char _letter = ' ';

public:
    UserInputMessage(const UserEventType &event) : _event(event) {}

    UserInputMessage(const UserEventType &event, const char &letter) : _event(event) {
        _letter = letter;
    }

    const char &getUserLetter() const {
        return _letter;
    }

    const UserEventType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP
