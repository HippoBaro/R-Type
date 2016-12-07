//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(new RTypeGameContext()), _menuContext(new RTypeMenuContext()) {

}

void SFMLManager::Run() {
    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    sf::RenderWindow _window(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);
    // Boucle de jeu.
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);

        sf::RenderTexture context;
        _gameContext->Draw(context, _textureBag);

        sf::Sprite sprite(context.getTexture());
        _window.draw(sprite);
        _window.display();
    }
}
