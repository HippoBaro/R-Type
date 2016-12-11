//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUCREATEROOM_HPP
#define R_TYPE_MENUCREATEROOM_HPP

#include "DrawableMenu/ADrawableInputMenu.hpp"

class MenuCreateRoom : public ADrawableInputMenu {
public:
    MenuCreateRoom(std::shared_ptr<RType::EventManager> &eventManager);
};


#endif //R_TYPE_MENUCREATEROOM_HPP
