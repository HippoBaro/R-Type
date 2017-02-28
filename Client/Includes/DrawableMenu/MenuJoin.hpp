//
// Created by pasteu_e on 10/12/16.
//

#ifndef R_TYPE_MENUJOIN_HPP
#define R_TYPE_MENUJOIN_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuJoin : public ADrawableMenu {
private:
    std::string _textToWrite;
public:
    MenuJoin(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override;
};

#endif //R_TYPE_MENUJOIN_HPP
