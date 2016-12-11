//
// Created by pasteu_e on 11/12/16.
//

#ifndef R_TYPE_ADRAWABLEINPUTMENU_HPP
#define R_TYPE_ADRAWABLEINPUTMENU_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class ADrawableInputMenu : public ADrawableMenu {
private:
    bool _blinkingCursor = true;
    int _frame = 0;
    std::string _drawableTextByUser = "_";
    RType::EventListener _eventListener;

public:
    ADrawableInputMenu(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override final;

    const std::string getChannelName() override final;
};


#endif //R_TYPE_ADRAWABLEINPUTMENU_HPP
