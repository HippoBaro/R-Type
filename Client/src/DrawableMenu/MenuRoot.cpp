//
// Created by pasteu_e on 08/12/16.
//

#include "DrawableMenu/MenuRoot.hpp"

MenuRoot::MenuRoot(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Create Room");
    _menuMap[1] = std::make_pair(false, "Join Room");
    _menuMap[2] = std::make_pair(false, "Settings");
    _menuMap[3] = std::make_pair(false, "Quit");
    _menuName = "Back";
    _menuType = VERTICAL;
    _active = true;
}