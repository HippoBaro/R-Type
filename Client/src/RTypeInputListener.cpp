//
// Created by pasteu_e on 27/11/16.
//

#include <iostream>
#include <Messages/UserInputMessage.hpp>
#include "RTypeInputListener.hpp"


RTypeInputListener::RTypeInputListener(std::shared_ptr<RType::EventManager> eventManager) : _eventManager(eventManager) {
}

void RTypeInputListener::CheckForInputs(sf::Window &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                KeyBoardEvent(event.key.code);
                break;
            default:
                break;
        }
    }
}

void RTypeInputListener::KeyBoardEvent(sf::Keyboard::Key &key) {
    switch (key) {
        case sf::Keyboard::Left:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_LEFT), this);
            break;
        case sf::Keyboard::Right:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_RIGHT), this);
            break;
        case sf::Keyboard::Up:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_UP), this);
            break;
        case sf::Keyboard::Down:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_DOWN), this);
            break;
        case sf::Keyboard::Space:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_SPACE), this);
            break;
        case sf::Keyboard::Return:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_ENTER), this);
            break;
        case sf::Keyboard::Escape:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_ESCAPE), this);
            break;
        case sf::Keyboard::BackSpace:
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_LETTER, '\b'), this);
            break;
        default:
            if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
                _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(USER_LETTER, key + 65), this);
            break;
    }
}