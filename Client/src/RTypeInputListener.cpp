//
// Created by pasteu_e on 27/11/16.
//

#include "RTypeInputListener.hpp"


RTypeInputListener::RTypeInputListener(std::shared_ptr<RType::EventManager> eventManager) : _eventManager(eventManager) { }

void RTypeInputListener::CheckForInputs(sf::Window &window) {
    auto eventKey = new UserInputMessage();

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                _keyPressed.insert(event.key.code);
                KeyBoardInputEvent(event.key.code);
                break;
            case sf::Event::KeyReleased:
                _keyPressed.erase(event.key.code);
                SubscribeReleasedKeys(eventKey, event.key.code);
            default:
                break;
        }
    }
    SubscribePressedKeys(eventKey);
    if (eventKey->AnyPressed() || eventKey->AnyReleased())
        _eventManager->Emit(UserInputMessage::EventType, eventKey, this);
    else
        delete eventKey;
}

void RTypeInputListener::KeyBoardInputEvent(sf::Keyboard::Key &key) {
    if (key == sf::Keyboard::BackSpace)
        _eventManager->Emit(UserInputEntryMessage::EventType, new UserInputEntryMessage('\b'), this);
    else if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
        _eventManager->Emit(UserInputEntryMessage::EventType, new UserInputEntryMessage(key + 65), this);
}

void RTypeInputListener::SubscribePressedKeys(UserInputMessage *event) {
    for (auto &key : _keyPressed) {
        event->AddPressedEvent(ConvertSfmlEvent(key));
    }
}

void RTypeInputListener::SubscribeReleasedKeys(UserInputMessage *event, const sf::Keyboard::Key &releasedKey) {
    event->AddReleasedEvent(ConvertSfmlEvent(releasedKey));
}

UserEventType RTypeInputListener::ConvertSfmlEvent(const sf::Keyboard::Key &key) {
    if (key == sf::Keyboard::Left)
        return USER_LEFT;
    if (key == sf::Keyboard::Right)
        return USER_RIGHT;
    if (key == sf::Keyboard::Up)
        return USER_UP;
    if (key == sf::Keyboard::Down)
        return USER_DOWN;
    if (key == sf::Keyboard::Space)
        return USER_SPACE;
    if (key == sf::Keyboard::Return)
        return USER_ENTER;
    if (key == sf::Keyboard::Escape)
       return USER_ESCAPE;
    return OTHER;
}
