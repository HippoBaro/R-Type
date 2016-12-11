//
// Created by pasteu_e on 11/12/16.
//

#ifndef R_TYPE_SOUNDSYSTEMMESSAGE_HPP
#define R_TYPE_SOUNDSYSTEMMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>

enum SoundSystemEventType {
    PLAY_SOUND,
    VOLUME_SOUND,
    VOLUME_MUSIC
};

class SoundSystemMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::SOUND_SYSTEM;

private:
    const SoundSystemEventType _event;
    std::string _playSound = "";
    int _volume = 0;

public:
    SoundSystemMessage(const SoundSystemEventType &event) : _event(event) {}

    SoundSystemMessage(const SoundSystemEventType &event, const std::string &sound) : _event(event) {
        _playSound = sound;
    }

    SoundSystemMessage(const SoundSystemEventType &event, const int &volume) : _event(event) {
        _volume = volume;
    }

    const std::string &getPlaySound() const {
        return _playSound;
    }

    const int &getVolume() const {
        return _volume;
    }

    const SoundSystemEventType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_SOUNDSYSTEMMESSAGE_HPP
