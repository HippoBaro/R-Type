//
// Created by pasteu_e on 10/12/16.
//

#ifndef R_TYPE_MENUCREATE_HPP
#define R_TYPE_MENUCREATE_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuCreate : public ADrawableMenu {
public:
    MenuCreate(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override;
};

#endif //R_TYPE_MENUCREATE_HPP
