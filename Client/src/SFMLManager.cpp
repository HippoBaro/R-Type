//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>

SFMLManager::SFMLManager(std::shared_ptr<RType::EventManager> &eventManager) : _inputListener(new RTypeInputListener(eventManager)), _gameContext(new RTypeGameContext("sprites/testPartition.partition")), _menuContext(new RTypeMenuContext(eventManager)), _currentContext(), _eventManager(eventManager), _window(), _soundManager(new SoundManager(eventManager)) {
    _currentContext = std::move(_menuContext);
    RType::EventListener eventListener(eventManager);
    eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->getEventType() == CLOSE_WINDOWS) {
            _window.close();
        }
    });
    eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->getEventType() == PLAY_SOUND) {
            _soundManager->PlaySoundEffects(message->getPlaySound());
        } else if (message->getEventType() == USER_WAITING) {
            std::cout << message->getChannelName() << std::endl;
            //_currentContext = std::move(_gameContext);
        } else if (message->getEventType() == USER_STOP_WAITING) {
            std::cout << "Stop Waiting" << std::endl;
        }
    });
}

void SFMLManager::Run() {
    _soundManager->PlayMusic(true, "sprites/menuBackground.ogg");
    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    _window.create(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    glEnable(GL_TEXTURE_2D);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    sf::RenderTexture context;
    sf::Sprite renderSprite;
    context.create(Width, Height);

    // Boucle de jeu.
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);
        _currentContext->Draw(context, _textureBag);
        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();
    }
    _soundManager->StopMusic();
    _soundManager->StopSound();
}
