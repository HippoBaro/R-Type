//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>
#include <Messages/StopReceiveNetworkGamePayload.hpp>
#include <Messages/ClientWaitForServerMessage.hpp>
#include <Entities/PlayerRef.hpp>
#include <Messages/MenuStateUpdateMessage.hpp>

SFMLManager::SFMLManager(std::shared_ptr<RType::EventManager> &eventManager, std::shared_ptr<RTypeNetworkClient> &networkClient)
        : _inputListener(new RTypeInputListener(eventManager)), _gameContext(new RTypeGameContext(eventManager)),
          _menuContext(new RTypeMenuContext(eventManager)), _currentContext(), _eventManager(eventManager), _window(),
          _networkClient(networkClient), _soundManager(new SoundManager(eventManager)) {
    _currentContext = _menuContext.get();
    _eventListener = std::unique_ptr<RType::EventListener>(new RType::EventListener(_eventManager));
    _eventListener->Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->ReleasedContains(CLOSE_WINDOWS))
            _window.close();
    });
    _eventListener->Subscribe<Entity, SoundSystemMessage>(SoundSystemMessage::EventType, [&](Entity *, SoundSystemMessage *message) {
        if (message->getEventType() == PLAY_SOUND)
            _soundManager->PlaySoundEffects(message->getPlaySound());
    });
    _eventListener->Subscribe<Entity, ClientWaitForServerMessage>(ClientWaitForServerMessage::EventType, [&](Entity *, ClientWaitForServerMessage *message) {
        if (message->getEventType() == USER_CREATE || message->getEventType() == USER_JOIN)
            _roomName = message->getChannelName();
        else if (message->getEventType() == USER_READY || message->getEventType() == USER_QUIT)
            message->setChannelName(_roomName);
        RType::Packer packer(RType::WRITE);
        message->Serialize(packer);
        _networkClient->TryToSend(-1, RTypeNetworkPayload(packer));

    });
}

void SFMLManager::CheckForNetwork() {
    if (!_isConnected)
        _isConnected = _networkClient->TryToConnect();
    else {
        char data[1500];
        auto payload = RTypeNetworkPayload(data, 1500);
        if (_networkClient->TryReceive(0, payload)) {

            auto state = new MenuStateUpdateMessage();
            auto packer = RType::Packer(RType::READ, payload.Payload);
            packer.PackSerializables(state->getPlayers());

            _eventManager->Emit(MenuStateUpdateMessage::EventType, state, this);
        }
    }
}

void SFMLManager::Run() {
    _soundManager->PlayMusic(true, "medias/sounds/menuBackground.ogg");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    _window.create(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    glEnable(GL_TEXTURE_2D);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(false);

    sf::RenderTexture context;
    sf::Sprite renderSprite;
    context.create(Width, Height);
    sf::Clock clock;

    int minFPS = 60;
    int maxFPS = 0;

    // Boucle de jeu.
    while (_window.isOpen()) {
        if (_switch) {
            _currentContext = _gameContext.get();
            _currentContext->Setup("medias/partitions/testPartition.partition");
            _switch = !_switch;
            _menuContext->ReleaseListener();
            minFPS = 60;
            maxFPS = 0;
        }
        _inputListener->CheckForInputs(_window);
        if (_currentContext == _menuContext.get())
            CheckForNetwork();
        _currentContext->Draw(context, _textureBag);
        renderSprite.setTexture(context.getTexture());
        _window.draw(renderSprite);
        _window.display();

        sf::Time frameTime = clock.restart();
        std::stringstream stream;
        int current = 1000 / frameTime.asMilliseconds();
        if (maxFPS < current)
            maxFPS = current;
        else if (minFPS > current)
            minFPS = current;
        stream << "RTYPE | " << "[CURRENT = " << current << " MIN = " << minFPS << " MAX = " << maxFPS << "]";

        _window.setTitle(stream.str());
    }
    _eventManager->Emit(StopReceiveNetworkGamePayload::EventType, new StopReceiveNetworkGamePayload(), this);
    _soundManager->StopMusic();
    _soundManager->StopSound();
}
