//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_SOUNDMANAGER_HPP
#define R_TYPE_SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <thread>

class SoundManager {
private:
    float _soundVolume = 50;
    float _musicVolume = 50;
    sf::Music _music;
    sf::Sound _sound;
    std::map<std::string, sf::SoundBuffer> _cachedSound;

public:
    SoundManager();

    void PlayMusic(bool loop, const std::string &path);

    void setMusicVolume(float volume);

    void StopMusic();

    void PlaySound(const std::string &path);

    void setSoundVolume(float volume);

    void StopSound();
};


#endif //R_TYPE_SOUNDMANAGER_HPP
