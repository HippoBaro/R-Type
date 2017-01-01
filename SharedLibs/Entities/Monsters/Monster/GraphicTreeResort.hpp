//
// Created by barre_k
//

#ifndef R_TYPE_GRAPHICTENTACLEBOSS_HPP
#define R_TYPE_GRAPHICTENTACLEBOSS_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "TreeResort.hpp"

class GraphicTreeResort : public TreeResort, public AAnimatable {

public:
    GraphicTreeResort(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_GRAPHICTENTACLEBOSS_HPP
