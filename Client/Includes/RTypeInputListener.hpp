//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEINPUTLISTENER_HPP
#define R_TYPE_RTYPEINPUTLISTENER_HPP


#include <functional>
#include <SFML/Window.hpp>

class RTypeInputListener {
public:
    void CheckForInputs(sf::Window &window);

private:
    void KeyBoardEvent(sf::Keyboard::Key);
    void MouseEvent(sf::Mouse::Button);
};


#endif //R_TYPE_RTYPEINPUTLISTENER_HPP
