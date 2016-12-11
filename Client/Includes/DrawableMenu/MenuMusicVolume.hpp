//
// Created by pasteu_e on 10/12/16.
//

#ifndef R_TYPE_MENUMUSICVOLUME_HPP
#define R_TYPE_MENUMUSICVOLUME_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuMusicVolume : public ADrawableMenu {
private:
    int _volume = 50;
    RType::EventListener _eventListener;

public:
    MenuMusicVolume(std::shared_ptr<RType::EventManager> &eventManager);

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override;
};

#endif //R_TYPE_MENUMUSICVOLUME_HPP
