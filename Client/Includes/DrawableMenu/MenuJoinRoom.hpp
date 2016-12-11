//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUJOINROOM_HPP
#define R_TYPE_MENUJOINROOM_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuJoinRoom : public ADrawableMenu {
private:
    bool _blinkingCursor = true;
    int _frame = 0;
    std::string _drawableTextByUser = "_";
    RType::EventListener _eventListener;

public:
    MenuJoinRoom(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override;

    const std::string getChannelName() override;
};


#endif //R_TYPE_MENUJOINROOM_HPP
