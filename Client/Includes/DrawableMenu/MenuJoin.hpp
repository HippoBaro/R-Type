//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUJOIN_HPP
#define R_TYPE_MENUJOIN_HPP


#include "DrawableMenu/ADrawableMenu.hpp"

class MenuJoin : public ADrawableMenu {
public:
    MenuJoin() {
        _menuMap[0] = std::make_pair(true, "Back");
        _menuMap[1] = std::make_pair(false, "Join");
        _menuName = "Join Room";
        _menuType = HORIZONTAL;
    }
};


#endif //R_TYPE_MENUJOIN_HPP
