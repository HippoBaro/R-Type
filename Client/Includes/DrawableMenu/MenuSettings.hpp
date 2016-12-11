//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUSETTINGS_HPP
#define R_TYPE_MENUSETTINGS_HPP


#include "DrawableMenu/ADrawableMenu.hpp"

class MenuSettings : public ADrawableMenu {
public:
    MenuSettings(std::shared_ptr<RType::EventManager> &eventManager);
};


#endif //R_TYPE_MENUSETTINGS_HPP
