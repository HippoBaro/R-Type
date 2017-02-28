//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUROOT_HPP
#define R_TYPE_MENUROOT_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuRoot : public ADrawableMenu {
public:
    MenuRoot(std::shared_ptr<RType::EventManager> &eventManager);
};


#endif //R_TYPE_MENUROOT_HPP
