//
// Created by barre_k
//

#ifndef R_TYPE_GRAPHICTANK_HPP
#define R_TYPE_GRAPHICTANK_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "Tank.hpp"

class GraphicTank : public Tank, public AAnimatable {

public:
    GraphicTank(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_GRAPHICTANK_HPP
