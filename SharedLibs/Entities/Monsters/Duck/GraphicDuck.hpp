//
// Created by barre_k
//

#ifndef R_TYPE_GRAPHICDUCK_HPP
#define R_TYPE_GRAPHICDUCK_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "Duck.hpp"

class GraphicDuck : public Duck, public AAnimatable {

public:
    GraphicDuck(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};

F
#endif //R_TYPE_GRAPHICDuck_HPP
