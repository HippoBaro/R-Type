//
// Created by pasteu_e on 27/11/16.
//

#include <iostream>
#include "RTypeInputListener.hpp"

//TODO : Remove all output and send event to NetworkClient by eventEmitter

void RTypeInputListener::CheckForInputs(sf::Window &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                std::cout << "Close window event." << std::endl;
                window.close();
                break;
            case sf::Event::KeyPressed:
                KeyBoardEvent(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                MouseEvent(event.mouseButton.button);
                break;
            default:
                break;
        }
    }
}

void RTypeInputListener::KeyBoardEvent(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Left:
            std::cout << "Press Left" << std::endl;
            break;
        case sf::Keyboard::Right:
            std::cout << "Press Right" << std::endl;
            break;
        case sf::Keyboard::Up:
            std::cout << "Press Up" << std::endl;
            break;
        case sf::Keyboard::Down:
            std::cout << "Press Down" << std::endl;
            break;
        default:
            break;
    }
}

void RTypeInputListener::MouseEvent(sf::Mouse::Button button) {
    switch (button) {
        case sf::Mouse::Left:
            std::cout << "Left Click" << std::endl;
            break;
        case sf::Mouse::Right:
            std::cout << "Right Click" << std::endl;
            break;
        default:
            break;

    }
}
