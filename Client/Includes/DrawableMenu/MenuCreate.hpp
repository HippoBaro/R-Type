//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUCREATE_HPP
#define R_TYPE_MENUCREATE_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuCreate : public ADrawableMenu {
public:
    MenuCreate() {
        _menuMap[0] = std::make_pair(true, "Back");
        _menuMap[1] = std::make_pair(false, "Create");
        _menuName = "Create Room";
        _menuType = HORIZONTAL;
    }
};


#endif //R_TYPE_MENUCREATE_HPP
