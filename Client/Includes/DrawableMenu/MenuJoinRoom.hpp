//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUJOINROOM_HPP
#define R_TYPE_MENUJOINROOM_HPP

#include "DrawableMenu/ADrawableInputMenu.hpp"

class MenuJoinRoom : public ADrawableInputMenu {
public:
    MenuJoinRoom(std::shared_ptr<RType::EventManager> &eventManager);
};


#endif //R_TYPE_MENUJOINROOM_HPP
