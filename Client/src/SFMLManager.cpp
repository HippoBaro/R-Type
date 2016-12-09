//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>

std::unique_ptr<SoundManager> SFMLManager::soundManager = std::unique_ptr<SoundManager>(new SoundManager());

SFMLManager::SFMLManager(std::shared_ptr<RType::EventManager> eventManager) : _inputListener(new RTypeInputListener(eventManager)), _gameContext(new RTypeGameContext()), _menuContext(new RTypeMenuContext(eventManager)), _eventManager(eventManager), _window() {
    RType::EventListener eventListener(eventManager);
    eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->getEventType() == CLOSE_WINDOWS) {
            _window.close();
        }
    });
}

void SFMLManager::Run() {
    soundManager->PlayMusic(true, "sprites/menuBackground.ogg");
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
        _menuContext->Draw(context, _textureBag);
        //_gameContext->Draw(context, _textureBag);
        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();
    }
    SFMLManager::soundManager->StopMusic();
    SFMLManager::soundManager->StopSound();
}
