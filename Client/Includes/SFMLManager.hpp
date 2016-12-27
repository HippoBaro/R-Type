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
#include "RTypeNetworkClient.hpp"
#include <Messages/UserInputMessage.hpp>
#include <EventDispatcher/EventManager.hpp>

constexpr int Width = 1280;
constexpr int Height = 720;

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRTypeDrawingContext> _gameContext;
    std::unique_ptr<IRTypeDrawingContext> _menuContext;
    IRTypeDrawingContext *_currentContext;
    TextureBag _textureBag = TextureBag();
    std::shared_ptr<RType::EventManager> _eventManager;
    std::unique_ptr<RType::EventListener> _eventListener;
    sf::RenderWindow _window;
    bool _switch = false;
    bool _isMenu = true;
    bool _isConnected = false;
    bool _tryToCreate = false;
    bool _tryToJoin = false;
    bool _tryToReady = false;
    bool _tryToQuit = false;
    std::string _roomName = "";
    std::shared_ptr<RTypeNetworkClient> _networkClient;

private:
    void CheckForNetwork();
public:
    std::unique_ptr<SoundManager> _soundManager;
    SFMLManager(std::shared_ptr<RType::EventManager> &eventManager, std::shared_ptr<RTypeNetworkClient> &networkClient);
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
