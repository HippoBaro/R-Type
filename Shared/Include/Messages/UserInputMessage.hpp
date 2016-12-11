//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_USERINPUTMESSAGE_HPP
#define R_TYPE_USERINPUTMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>
#include <cdaudio.h>

enum UserEventType {
    CLOSE_WINDOWS,
    USER_UP,
    USER_DOWN,
    USER_RIGHT,
    USER_LEFT,
    USER_SPACE,
    USER_ENTER,
    USER_ESCAPE,
    PLAY_SOUND,
    USER_LETTER,
    VOLUME_SOUND,
    VOLUME_MUSIC,
    USER_WAITING,
    USER_STOP_WAITING
};

class UserInputMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT;

private:
    const UserEventType _event;
    std::string _playSound = "";
    std::string _channelName = "";
    char _letter = ' ';
    int _volume = 0;

public:
    UserInputMessage(const UserEventType &event) : _event(event) {}

    UserInputMessage(const UserEventType &event, const std::string &sound) : _event(event) {
        _playSound = sound;
    }

    UserInputMessage(const std::string &channelName, const UserEventType &event) : _event(event) {
        _channelName = channelName;
    }

    UserInputMessage(const UserEventType &event, const char &letter) : _event(event) {
        _letter = letter;
    }

    UserInputMessage(const int &volume, const UserEventType &event) : _event(event) {
        _volume = volume;
    }

    const std::string &getPlaySound() const {
        return _playSound;
    }

    const std::string &getChannelName() const {
        return _channelName;
    }

    const char &getUserLetter() const {
        return _letter;
    }

    const int &getVolume() const {
        return _volume;
    }

    const UserEventType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_USERINPUTMESSAGE_HPP
