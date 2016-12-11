//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_GRAPHICSHIP_HPP
#define R_TYPE_GRAPHICSHIP_HPP

#include <IDrawable.hpp>
#include "Ship.hpp"

class GraphicShip : public Ship, public IDrawable {

public:
    GraphicShip(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Cycle() override;
};

#endif //R_TYPE_GRAPHICSHIP_HPP
