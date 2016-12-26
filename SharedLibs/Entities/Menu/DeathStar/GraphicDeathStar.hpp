//
// Created by pasteu_e on 07/12/16.
//

#ifndef R_TYPE_DRAWABLEPLANET_HPP
#define R_TYPE_DRAWABLEPLANET_HPP

#include <IDrawable.hpp>
#include "DeathStar.hpp"

class GraphicDeathStar : public DeathStar, public AAnimable {

public:
    GraphicDeathStar(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;

    virtual bool NeedRedraw() override ;
};

#endif //R_TYPE_DRAWABLEPLANET_HPP
