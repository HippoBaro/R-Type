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
    _window.create(sf::VideoMode(WIDTH, HEIGHT), "RType");
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    // Boucle de jeu.
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);
        _window.clear(sf::Color::Black);
        _window.display();
    }
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
}