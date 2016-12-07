//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_SFMLMANAGER_HPP
#define R_TYPE_SFMLMANAGER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IRtypeDrawingContext.hpp"
#include "RTypeInputListener.hpp"
#include "TextureBag.hpp"

constexpr int Width = 1280;
constexpr int Height = 720;

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRtypeDrawingContext> _gameContext;
    std::unique_ptr<IRtypeDrawingContext> _menuContext;
    TextureBag _textureBag = TextureBag();

public:
    SFMLManager();
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
