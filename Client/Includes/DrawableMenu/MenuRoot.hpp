//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUROOT_HPP
#define R_TYPE_MENUROOT_HPP


#include "DrawableMenu/ADrawableMenu.hpp"

class MenuRoot : public ADrawableMenu {
public:
    MenuRoot() {
        _menuMap[0] = std::make_pair(true, "Create Room");
        _menuMap[1] = std::make_pair(false, "Join Room");
        _menuMap[2] = std::make_pair(false, "Settings");
        _menuMap[3] = std::make_pair(false, "Quit");
        _menuName = "Back";
        _menuType = VERTICAL;
        _active = true;
    }
};


#endif //R_TYPE_MENUROOT_HPP
