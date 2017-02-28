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
    OTHER
};

class UserInputMessage : public IMessage, RType::ISerializable {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    std::set<UserEventType> _keyPressed;
    std::set<UserEventType> _keyReleased;

public:
    UserInputMessage() : _keyPressed(), _keyReleased() {}

    UserInputMessage(UserEventType event) : _keyPressed(), _keyReleased() {
        _keyPressed.insert(event);
    }

    virtual void Serialize(RType::Packer &packer) {
        packer.Pack(_keyPressed);
    }

    const std::set<UserEventType> &getPressed() const {
        return _keyPressed;
    }

    bool PressedContains(UserEventType event) {
        return _keyPressed.count(event) > 0;
    }

    bool PressedContainsOnly(UserEventType event) {
        return _keyPressed.count(event) == 1 && _keyPressed.size() == 1;
    }

    UserEventType FirstPressed() {
        return *_keyPressed.begin();
    }

    void AddPressedEvent(UserEventType event) {
        _keyPressed.insert(event);
    }

    bool AnyPressed() {
        return _keyPressed.size() > 0;
    }

    const std::set<UserEventType> &getReleased() const {
        return _keyReleased;
    }

    bool ReleasedContains(UserEventType event) {
        return _keyReleased.count(event) > 0;
    }

    bool ReleasedContainsOnly(UserEventType event) {
        return _keyReleased.count(event) == 1 && _keyReleased.size() == 1;
    }

    UserEventType FirstReleased() {
        return *_keyReleased.begin();
    }

    void AddReleasedEvent(UserEventType event) {
        _keyReleased.insert(event);
    }

    bool AnyReleased() {
        return _keyReleased.size() > 0;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP