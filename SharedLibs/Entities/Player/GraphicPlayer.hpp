//
// Created by hippolyteb on 11/29/16.
//

#ifndef R_TYPE_GRAPHICPLAYER_HPP
#define R_TYPE_GRAPHICPLAYER_HPP

#include <IDrawable.hpp>
#include "Player.hpp"

class GraphicPlayer : public Player, public IDrawable {

public:
    GraphicPlayer(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    virtual bool NeedRedraw() override ;
    void Cycle() override;
};

#endif //R_TYPE_GRAPHICPLAYER_HPP
