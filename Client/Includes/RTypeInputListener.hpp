//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEINPUTLISTENER_HPP
#define R_TYPE_RTYPEINPUTLISTENER_HPP

#include <functional>
#include <set>
#include <SFML/Window.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <iostream>
#include <Messages/UserInputMessage.hpp>
#include <Messages/UserInputEntryMessage.hpp>

class RTypeInputListener {
private:
    std::shared_ptr<RType::EventManager> _eventManager;
    std::set<sf::Keyboard::Key> _keyPressed;

    void KeyBoardInputEvent(sf::Keyboard::Key &);
    void SubscribePressedKeys(UserInputMessage *event);
    void SubscribeReleasedKeys(UserInputMessage *event, const sf::Keyboard::Key &releasedKey);

    UserEventType ConvertSfmlEvent(const sf::Keyboard::Key &key);

public:
    RTypeInputListener(std::shared_ptr<RType::EventManager> eventManager);

    void CheckForInputs(sf::Window &window);

};


#endif //R_TYPE_RTYPEINPUTLISTENER_HPP
