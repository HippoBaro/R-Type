//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_IDRAWABLEMENU_HPP
#define R_TYPE_IDRAWABLEMENU_HPP

#include <utility>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Messages/UserInputMessage.hpp"

enum MenuType {
    VERTICAL,
    HORIZONTAL
};

class ADrawableMenu {
protected:
    std::map<int, std::pair<bool, std::string>> _menuMap = std::map<int, std::pair<bool, std::string>>();
    std::string _menuName = std::string();
    MenuType _menuType = VERTICAL;
    bool _active = false;

public:
    virtual ~ADrawableMenu() {}

    void moveSelection(UserEventType type) {
        if (_active) {
            if (_menuType == VERTICAL) {
                for (auto &elem : _menuMap) {
                    if (elem.second.first) {
                        if (type == USER_DOWN && (unsigned long) elem.first < _menuMap.size() - 1) {
                            elem.second.first = !elem.second.first;
                            _menuMap[elem.first + 1] = std::make_pair(!_menuMap[elem.first + 1].first, _menuMap[elem.first + 1].second);
                            break;
                        } else if (type == USER_UP && elem.first > 0) {
                            elem.second.first = !elem.second.first;
                            _menuMap[elem.first - 1] = std::make_pair(!_menuMap[elem.first - 1].first, _menuMap[elem.first - 1].second);
                            break;
                        }
                    }
                }
            }
        }
    }

    static void moveIn(std::vector<std::unique_ptr<ADrawableMenu>> &_menu) {
        std::string nextMenu;
        for (auto &&elem : _menu) {
            if (elem->_active) {
                for (auto &subElem : elem->_menuMap) {
                    if (subElem.second.first) {
                        nextMenu = subElem.second.second;
                        for (auto &&tmpElem : _menu) {
                            if (tmpElem->_menuName == nextMenu) {
                                tmpElem->_active = !tmpElem->_active;
                                elem->_active = !elem->_active;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    void Draw(sf::RenderTexture &context, sf::Text &text) {
        if (_active) {
            if (_menuType == VERTICAL) {
                int i = 1;
                long y = (context.getSize().y / 2) - (((50 * _menuMap.size()) + (50 * (_menuMap.size() - 2))) / 2);
                for (auto &elem : _menuMap) {
                    std::pair<bool, std::string> value = elem.second;
                    if (elem.second.first)
                        text.setFillColor(sf::Color::Red);
                    else
                        text.setFillColor(sf::Color::White);
                    text.setString(elem.second.second);
                    text.setPosition(150, y + (50 * i));
                    context.draw(text);
                    i++;
                }
            }
        }
    }
};

#endif //R_TYPE_IDRAWABLEMENU_HPP
