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
    CLOSE_WINDOWS,
    OTHER
};

class UserInputMessage : public IMessage, RType::ISerializable {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    std::set<UserEventType> keyPressed;
    std::set<UserEventType> keyReleased;

public:
    UserInputMessage() : keyPressed() {}

    UserInputMessage(UserEventType event) : keyPressed() {
        keyPressed.insert(event);
    }

    virtual void Serialize(RType::Packer &packer) {
        packer.Pack(keyPressed);
    }

    const std::set<UserEventType> &getPressed() const {
        return keyPressed;
    }

    bool PressedContains(UserEventType event) {
        return keyPressed.count(event) > 0;
    }

    bool PressedContainsOnly(UserEventType event) {
        return keyPressed.count(event) == 1 && keyPressed.size() == 1;
    }

    UserEventType FirstPressed() {
        return *keyPressed.begin();
    }

    void AddPressedEvent(UserEventType event) {
        keyPressed.insert(event);
    }

    bool AnyPressed() {
        return keyPressed.size() > 0;
    }

    const std::set<UserEventType> &getReleased() const {
        return keyReleased;
    }

    bool ReleasedContains(UserEventType event) {
        return keyReleased.count(event) > 0;
    }

    bool ReleasedContainsOnly(UserEventType event) {
        return keyReleased.count(event) == 1 && keyReleased.size() == 1;
    }

    UserEventType FirstReleased() {
        return *keyReleased.begin();
    }

    void AddReleasedEvent(UserEventType event) {
        keyReleased.insert(event);
    }

    bool AnyReleased() {
        return keyReleased.size() > 0;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP