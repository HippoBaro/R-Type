//
// Created by Etienne Pasteur on 01/01/2017.
//

#ifndef R_TYPE_MENUSELECTLEVEL_HPP
#define R_TYPE_MENUSELECTLEVEL_HPP


#include "ADrawableInputMenu.hpp"

class MenuSelectLevel : public ADrawableInputMenu {
public:
    MenuSelectLevel(std::shared_ptr<RType::EventManager> &eventManager);
    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override final;

};


#endif //R_TYPE_MENUSELECTLEVEL_HPP
