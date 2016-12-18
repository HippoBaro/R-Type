//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>
#include <Messages/SoundSystemMessage.hpp>
#include <Messages/MenuLobbyMessage.hpp>

SFMLManager::SFMLManager(std::shared_ptr<RType::EventManager> &eventManager) : _inputListener(new RTypeInputListener(eventManager)), _gameContext(new RTypeGameContext(eventManager)), _menuContext(new RTypeMenuContext(eventManager)), _currentContext(), _eventManager(eventManager), _window(), _soundManager(new SoundManager(eventManager)) {
    _currentContext = _menuContext.get();
    _eventListener = std::unique_ptr<RType::EventListener>(new RType::EventListener(_eventManager));
    _eventListener->Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->getEventType() == CLOSE_WINDOWS)
            _window.close();
    });
    _eventListener->Subscribe<Entity, SoundSystemMessage>(SoundSystemMessage::EventType, [&](Entity *, SoundSystemMessage *message) {
        if (message->getEventType() == PLAY_SOUND)
            _soundManager->PlaySoundEffects(message->getPlaySound());
    });
    _eventListener->Subscribe<Entity, MenuLobbyMessage>(MenuLobbyMessage::EventType, [&](Entity *, MenuLobbyMessage *message) {
        if (message->getEventType() == USER_WAITING) {
            std::cout << "Room name is: " << message->getChannelName() << std::endl;
            _switch = true;
        } else if (message->getEventType() == USER_STOP_WAITING)
            std::cout << "Stop Waiting" << std::endl;
    });
}

void SFMLManager::Run() {
    _soundManager->PlayMusic(true, "medias/sounds/menuBackground.ogg");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    _window.create(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    glEnable(GL_TEXTURE_2D);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    sf::RenderTexture context;
    sf::Sprite renderSprite;
    context.create(Width, Height);
    _switch = true;

    // Boucle de jeu.
    while (_window.isOpen()) {
        if (_switch) {
            _currentContext = _gameContext.get();
            _currentContext->Setup("medias/partitions/testPartition.partition");
            _switch = !_switch;
            _menuContext->ReleaseListener();
        }
        _inputListener->CheckForInputs(_window);
        _currentContext->Draw(context, _textureBag);
        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();
    }
    _soundManager->StopMusic();
    _soundManager->StopSound();
}
