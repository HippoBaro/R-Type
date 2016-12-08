//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEINPUTLISTENER_HPP
#define R_TYPE_RTYPEINPUTLISTENER_HPP

#include <functional>
#include <SFML/Window.hpp>
#include <EventDispatcher/EventManager.hpp>

class RTypeInputListener {
private:
    std::shared_ptr<RType::EventManager> _eventManager;

    void KeyBoardEvent(sf::Keyboard::Key);
//    void MouseEvent(sf::Mouse::Button);

public:
    RTypeInputListener(std::shared_ptr<RType::EventManager> eventManager);

    void CheckForInputs(sf::Window &window);

};


#endif //R_TYPE_RTYPEINPUTLISTENER_HPP
