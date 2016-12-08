//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUSETTINGS_HPP
#define R_TYPE_MENUSETTINGS_HPP


#include "DrawableMenu/ADrawableMenu.hpp"

class MenuSettings : public ADrawableMenu {
public:
    MenuSettings() {
        _menuMap[0] = std::make_pair(false, "Music Volume");
        _menuMap[1] = std::make_pair(false, "Sound Volume");
        _menuMap[2] = std::make_pair(true, "Back");
        _menuName = "Settings";
        _menuType = VERTICAL;
    }
};


#endif //R_TYPE_MENUSETTINGS_HPP
