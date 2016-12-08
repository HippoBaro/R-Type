//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(nullptr), _menuContext(new RTypeMenuContext()), _soundManager(new SoundManager()) {

}

void SFMLManager::Run() {
    _soundManager->PlayMusic(true, "sprites/menuBackground.ogg");
    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    sf::RenderWindow _window(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");

    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    sf::RenderTexture context;
    sf::Sprite renderSprite;
    // Boucle de jeu.
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);

        _menuContext->Draw(context);
        //_gameContext->Draw(context, _textureBag);
        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();
    }
}
