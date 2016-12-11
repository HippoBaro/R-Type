//
// Created by pasteu_e on 08/12/16.
//

#include "DrawableMenu/MenuSettings.hpp"

MenuSettings::MenuSettings(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(false, "Music Volume");
    _menuMap[1] = std::make_pair(false, "Sound Volume");
    _menuMap[2] = std::make_pair(true, "Back");
    _menuName = "Settings";
    _menuType = VERTICAL;
}