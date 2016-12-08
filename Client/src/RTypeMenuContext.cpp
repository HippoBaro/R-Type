//
// Created by pasteu_e on 27/11/16.
//

#include <vec2.hpp>
#include <Time/Timer.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeMenuContext.hpp"
#include <utility>

RTypeMenuContext::RTypeMenuContext(std::shared_ptr<RType::EventManager> eventManager) : _eventManager(eventManager), _eventListener(eventManager) {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer);

    auto stratPos = vec2<float>(1500, 100);
    _pool->AddEntity("DeathStar", stratPos);

    stratPos = vec2<float>(1100, 450);
    _pool->AddEntity("Mars", stratPos);

    stratPos = vec2<float>(-100, -100);
    _pool->AddEntity("Ship", stratPos);


    _backgroundTexture.loadFromFile("sprites/spacebackground.png");
    _background.setTexture(_backgroundTexture);
    _font.loadFromFile("sprites/pdark.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(50);

    _menuRoot[0] = std::make_pair(true, "Create Room");
    _menuRoot[1] = std::make_pair(false, "Join Room");
    _menuRoot[2] = std::make_pair(false, "Settings");
    _menuRoot[3] = std::make_pair(false, "Quit");

    _menuSettings[0] = std::make_pair(false, "Music Volume");
    _menuSettings[1] = std::make_pair(false, "Sound Volume");
    _menuSettings[2] = std::make_pair(true, "Back");

    _currentMenu = _menuRoot;

    _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        switch (message->getEventType()) {
            case CLOSE_WINDOWS:
                break;
            case USER_UP:
                UpdateMenu(USER_UP, _currentMenu);
                break;
            case USER_DOWN:
                UpdateMenu(USER_DOWN, _currentMenu);
                break;
            case USER_RIGHT:
                break;
            case USER_LEFT:
                break;
            case USER_SPACE:
                break;
            case USER_ENTER:
                NextMenu(_currentMenu);
                break;
            case USER_ESCAPE:
                break;
        }
    });
}

void RTypeMenuContext::NextMenu(std::map<int, std::pair<bool, std::string>> &menu) {
    std::map<int, std::pair<bool, std::string>>::iterator it;

    for (it = menu.begin(); it != menu.end(); ++it) {
        if (it->second.first) {
            if (it->second.second == "Settings") {
                _currentMenu = _menuSettings;
                break;
            }
            if (it->second.second == "Quit") {
                _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(CLOSE_WINDOWS), this);
                _currentMenu = _menuSettings;
                break;
            }
            if (it->second.second == "Back") {
                _currentMenu = _menuRoot;
                break;
            }
        }
    }
}

void RTypeMenuContext::UpdateMenu(UserEventType type, std::map<int, std::pair<bool, std::string>> &menu) {
    std::map<int, std::pair<bool, std::string>>::iterator it;
    unsigned int i = 0;
    for (it = menu.begin(); it != menu.end(); ++it) {
        i++;
        if (it->second.first) {
            if (type == USER_DOWN && i != menu.size()) {
                it->second.first = false;
                ++it;
                it->second.first = true;
            } else if (type == USER_UP && i != 1) {
                it->second.first = false;
                --it;
                it->second.first = true;
            }
        }
    }
}

void RTypeMenuContext::DrawMenu(sf::RenderTexture &context, std::map<int, std::pair<bool, std::string>> &menu) {
    int i = 1;
    long y = (context.getSize().y / 2) - (((50 * menu.size()) + (50 * (menu.size() - 2))) / 2);
    for (auto &elem : menu) {
        std::pair<bool, std::string> value = elem.second;
        if (elem.second.first)
            _text.setFillColor(sf::Color::Red);
        else
            _text.setFillColor(sf::Color::White);
        _text.setString(elem.second.second);
        _text.setPosition(150, y + (50 * i));
        context.draw(_text);
        i++;
    }
}

void RTypeMenuContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.create(1280, 720);
    context.clear(sf::Color::Black);
    context.draw(_background);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    DrawMenu(context, _currentMenu);
    context.display();
}