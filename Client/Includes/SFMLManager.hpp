//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_SFMLMANAGER_HPP
#define R_TYPE_SFMLMANAGER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IRTypeDrawingContext.hpp"
#include "RTypeInputListener.hpp"
#include "SoundManager.hpp"

constexpr int Width = 1280;
constexpr int Height = 720;

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRTypeDrawingContext> _gameContext;
    std::unique_ptr<IRTypeDrawingContext> _menuContext;
    std::unique_ptr<SoundManager> _soundManager;

public:
    SFMLManager();
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
