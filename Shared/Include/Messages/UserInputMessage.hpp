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
    CLOSE_WINDOWS
};

class UserInputMessage : public IMessage, RType::ISerializable {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    std::set<UserEventType> _events;

public:
    UserInputMessage() : _events() {}

    UserInputMessage(UserEventType event) : _events() {
        _events.insert(event);
    }

    const std::set<UserEventType> &getEvents() const {
        return _events;
    }

    bool Contains(UserEventType event) {
        return _events.count(event) > 0;
    }

    bool ContainsOnly(UserEventType event) {
        return _events.count(event) == 1 && _events.size() == 1;
    }

    UserEventType First() {
        return *_events.begin();
    }

    void AddEvent(UserEventType event) {
        _events.insert(event);
    }

    virtual void Serialize(RType::Packer &packer) {
        packer.Pack(_events);
    }

    bool Any() {
        return _events.size() > 0;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP