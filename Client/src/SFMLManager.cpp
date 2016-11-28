//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(new RTypeGameContext()), _menuContext(new RTypeMenuContext()), _window() {

}

void SFMLManager::Run() {
    _window.create(sf::VideoMode(Width, Height), "RType");
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    // Boucle de jeu.
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);

        sf::RenderTexture context;
        _gameContext->Draw(context);

        sf::Sprite sprite(context.getTexture());
        _window.draw(sprite);
        _window.display();
    }
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
}




//        sf::RenderTexture renderTexture;
//        renderTexture.create(Width, Height);
//        renderTexture.clear();
//
//        sf::Texture texture;
//        texture.loadFromFile("sprites/r-typesheet1.gif", sf::IntRect(101, 3, 32, 14));
//        sf::Sprite sprite;
//        sprite.setTexture(texture);
//        sprite.setPosition(sf::Vector2f(10, 50));
//        sprite.setScale(sf::Vector2f(10.f, 10.f));
//
//        renderTexture.draw(sprite);
//        renderTexture.display();
//        const sf::Texture& textureDisplay = renderTexture.getTexture();
//        sf::Sprite DrawableSprite(textureDisplay);
//
//        _window.draw(DrawableSprite);
