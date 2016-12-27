//
// Created by aguado_e on 12/22/16.
//

#ifndef R_TYPE_GRAPHICTENTACLEBOSS_HPP
#define R_TYPE_GRAPHICTENTACLEBOSS_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "TentacleBoss.hpp"

class GraphicTentacleBoss : public TentacleBoss, public AAnimatable {

public:
    GraphicTentacleBoss(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_GRAPHICTENTACLEBOSS_HPP
