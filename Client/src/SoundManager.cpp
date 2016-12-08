//
// Created by pasteu_e on 08/12/16.
//

#include "SoundManager.hpp"

SoundManager::SoundManager() : _music(), _sound(), _cachedSound() {
}

void SoundManager::PlayMusic(bool loop, const std::string &path) {
    if (_music.openFromFile(path)) {
        _music.setLoop(loop);
        _music.setVolume(_musicVolume);
        _music.play();
    }

}

void SoundManager::setMusicVolume(float volume) {
    _musicVolume = volume;
    _music.setVolume(_musicVolume);
}

void SoundManager::StopMusic() {
    _music.stop();
}

void SoundManager::PlaySound(const std::string &path) {
    std::map<std::string, sf::SoundBuffer>::iterator it;

    it = _cachedSound.find(path);
    if (!(it != _cachedSound.end())) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(path)) {
            _cachedSound[path] = buffer;
        }
    }
    _sound.setBuffer(_cachedSound[path]);
    _sound.setVolume(_soundVolume);
    _sound.play();

}

void SoundManager::setSoundVolume(float volume) {
    _soundVolume = volume;
}

void SoundManager::StopSound() {
    _sound.stop();
}
