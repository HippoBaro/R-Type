//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(new RTypeGameContext()), _menuContext(new RTypeMenuContext()) {

}

void SFMLManager::Run() {
    sf::RenderTexture context;
    sf::Sprite renderSprite;

    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    sf::RenderWindow _window(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    glEnable(GL_TEXTURE_2D);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);
    // Boucle de jeu.
    sf::RenderTexture context;
    context.create(Width, Height);
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);

        _menuContext->Draw(context);
        //_gameContext->Draw(context);

        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();
    }
}
