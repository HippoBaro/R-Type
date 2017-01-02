//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_SOUNDMANAGER_HPP
#define R_TYPE_SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <thread>
#include <EventDispatcher/EventListener.hpp>

class SoundManager {
private:
    float _soundVolume = 0;
    float _musicVolume = 0;
    sf::Music _music;
    sf::Sound _sound;
    std::map<std::string, sf::SoundBuffer> _cachedSound;
    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;

public:
    SoundManager(std::shared_ptr<RType::EventManager> &eventManager);

    void PlayMusic(bool loop, const std::string &path);

    void setMusicVolume(float volume);

    void StopMusic();

    void PlaySoundEffects(const std::string &path);

    void setSoundVolume(float volume);

    void StopSound();
};


#endif //R_TYPE_SOUNDMANAGER_HPP
