//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_SFMLMANAGER_HPP
#define R_TYPE_SFMLMANAGER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IRtypeDrawingContext.hpp"
#include "RTypeInputListener.hpp"

#define WIDTH 800
#define HEIGHT 600

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRtypeDrawingContext> _gameContext;
    std::unique_ptr<IRtypeDrawingContext> _menuContext;
    sf::RenderWindow _window;

public:
    SFMLManager();
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
