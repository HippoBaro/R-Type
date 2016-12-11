//
// Created by pasteu_e on 08/12/16.
//

#include "DrawableMenu/MenuJoinRoom.hpp"

MenuJoinRoom::MenuJoinRoom(std::shared_ptr<RType::EventManager> &eventManager) : ADrawableInputMenu(eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuMap[1] = std::make_pair(false, "Join");
    _menuName = "Join Room";
    _menuType = HORIZONTAL;
}