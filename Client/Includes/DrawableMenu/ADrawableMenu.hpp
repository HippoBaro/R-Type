//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_IDRAWABLEMENU_HPP
#define R_TYPE_IDRAWABLEMENU_HPP

#include <utility>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Messages/UserInputMessage.hpp"

enum MenuType {
    VERTICAL,
    HORIZONTAL
};

class ADrawableMenu {
protected:
    std::shared_ptr<RType::EventManager> _eventManager = nullptr;
    std::map<int, std::pair<bool, std::string>> _menuMap = std::map<int, std::pair<bool, std::string>>();
    std::string _menuName = std::string();
    MenuType _menuType = VERTICAL;
    bool _active = false;

public:

    bool getActive() {
        return _active;
    }

    std::string &getMenuName() {
        return _menuName;
    }

    virtual ~ADrawableMenu() {}

    virtual void specialDrawing(sf::RenderTexture &context, sf::Text &text) {}

    virtual const std::string getChannelName() { return std::string(); }

    void moveSelection(UserEventType type) {
        if (_active && _menuName != "Music Volume" && _menuName != "Sound Volume") {
            for (auto &elem : _menuMap) {
                if (elem.second.first) {
                    if (((_menuType == VERTICAL && type == USER_DOWN) || (_menuType == HORIZONTAL && type == USER_RIGHT)) && (unsigned long) elem.first < _menuMap.size() - 1) {
                        elem.second.first = !elem.second.first;
                        _menuMap[elem.first + 1] = std::make_pair(!_menuMap[elem.first + 1].first, _menuMap[elem.first + 1].second);
                        _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(PLAY_SOUND, "sprites/changeMenu.ogg"), this);
                        break;
                    } else if (((_menuType == VERTICAL && type == USER_UP) || (_menuType == HORIZONTAL && type == USER_LEFT)) && elem.first > 0) {
                        elem.second.first = !elem.second.first;
                        _menuMap[elem.first - 1] = std::make_pair(!_menuMap[elem.first - 1].first, _menuMap[elem.first - 1].second);
                        _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(PLAY_SOUND, "sprites/changeMenu.ogg"), this);
                        break;
                    }
                }
            }
        }
    }

    static std::string moveIn(std::vector<std::unique_ptr<ADrawableMenu>> &_menu, std::shared_ptr<RType::EventManager> &_eventManager) {
        _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(PLAY_SOUND, "sprites/menuValidate.ogg"), nullptr);
        std::string nextMenu;
        for (auto &&elem : _menu) {
            if (elem->_active) {
                for (auto &subElem : elem->_menuMap) {
                    if (subElem.second.first) {
                        nextMenu = subElem.second.second;
                        if (nextMenu == "Quit") {
                            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1000));
                            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(CLOSE_WINDOWS), nullptr);
                        }
                        for (auto &&tmpElem : _menu) {
                            if (tmpElem->_menuName == nextMenu) {
                                tmpElem->_active = !tmpElem->_active;
                                elem->_active = !elem->_active;
                                return nextMenu;
                            }
                        }
                    }
                }
            }
        }
        return "";
    }

    void Draw(sf::RenderTexture &context, sf::Text &text) {
        if (_active) {
            float x = (context.getSize().x / 2.65f);
            float y = (context.getSize().y / 3.f);
            for (auto &elem : _menuMap) {
                std::pair<bool, std::string> value = elem.second;
                if (elem.second.first)
                    text.setFillColor(sf::Color::Red);
                else
                    text.setFillColor(sf::Color::White);
                text.setString(elem.second.second);
                if (_menuType == VERTICAL) {
                    text.setPosition(150, y);
                    y += 50;
                } else if (_menuType == HORIZONTAL) {
                    text.setPosition(x, 410);
                    x += (elem.second.second.size() * 50);
                }
                context.draw(text);
            }
            specialDrawing(context, text);
        }
    }
};

#endif //R_TYPE_IDRAWABLEMENU_HPP
