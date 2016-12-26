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

    void KeyBoardInputEvent(sf::Keyboard::Key &);
    void EmitPressedKey();

public:
    RTypeInputListener(std::shared_ptr<RType::EventManager> eventManager);

    void CheckForInputs(sf::Window &window, bool singleInput = true);

};


#endif //R_TYPE_RTYPEINPUTLISTENER_HPP
