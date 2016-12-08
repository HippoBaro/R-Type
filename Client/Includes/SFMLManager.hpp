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
#include "TextureBag.hpp"
#include <Messages/UserInputMessage.hpp>
#include <EventDispatcher/EventManager.hpp>

constexpr int Width = 1280;
constexpr int Height = 720;

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRTypeDrawingContext> _gameContext;
    std::unique_ptr<IRTypeDrawingContext> _menuContext;
    TextureBag _textureBag = TextureBag();
    std::shared_ptr<RType::EventManager> _eventManager;
    sf::RenderWindow _window;

public:
    static std::unique_ptr<SoundManager> soundManager;
    SFMLManager(std::shared_ptr<RType::EventManager> eventManager);
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
