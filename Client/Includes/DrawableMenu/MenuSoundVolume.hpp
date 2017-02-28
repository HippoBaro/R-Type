//
// Created by pasteu_e on 10/12/16.
//

#ifndef R_TYPE_MENUSOUNDVOLUME_HPP
#define R_TYPE_MENUSOUNDVOLUME_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuSoundVolume : public ADrawableMenu {
private:
    uint8_t _volume = 50;
    RType::EventListener _eventListener;

public:
    MenuSoundVolume(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override;
};

#endif //R_TYPE_MENUSOUNDVOLUME_HPP
