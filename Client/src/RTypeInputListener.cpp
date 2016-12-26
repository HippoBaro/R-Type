//
// Created by pasteu_e on 27/11/16.
//

#include <iostream>
#include <Messages/UserInputMessage.hpp>
#include <Messages/UserInputEntryMessage.hpp>
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
    auto eventKey = new UserInputMessage();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        eventKey->AddEvent(USER_LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        eventKey->AddEvent(USER_RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        eventKey->AddEvent(USER_UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        eventKey->AddEvent(USER_DOWN);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        eventKey->AddEvent(USER_SPACE);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        eventKey->AddEvent(USER_ENTER);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        eventKey->AddEvent(USER_ESCAPE);

    if (eventKey->Any()) {
        _eventManager->Emit(UserInputMessage::EventType, eventKey, this);
        return;
    }

    delete eventKey;

    switch (key) {
        case sf::Keyboard::BackSpace:
            _eventManager->Emit(UserInputEntryMessage::EventType,new UserInputEntryMessage('\b'), this);
            break;
        default:
            if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
                _eventManager->Emit(UserInputEntryMessage::EventType, new UserInputEntryMessage(key + 65), this);
            break;
    }
}