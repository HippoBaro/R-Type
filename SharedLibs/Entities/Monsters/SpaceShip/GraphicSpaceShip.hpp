//
// Created by barre_k
//

#ifndef R_TYPE_GRAPHICSPACESHIP_HPP
#define R_TYPE_GRAPHICSPACESHIP_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "SpaceShip.hpp"

class GraphicSpaceShip : public SpaceShip, public AAnimatable {

public:
    GraphicSpaceShip(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_GRAPHICSPACESHIP_HPP
