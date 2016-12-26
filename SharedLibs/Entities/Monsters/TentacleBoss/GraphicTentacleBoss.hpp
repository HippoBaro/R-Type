//
// Created by aguado_e on 12/22/16.
//

#ifndef R_TYPE_GRAPHICTENTACLEBOSS_HPP
#define R_TYPE_GRAPHICTENTACLEBOSS_HPP

#include <AAnimable.hpp>
#include <TextureBag.hpp>
#include "TentacleBoss.hpp"

class GraphicTentacleBoss : public TentacleBoss, public AAnimable {

public:
  GraphicTentacleBoss(const std::initializer_list<void *> init);

public:
  void Draw(sf::RenderTexture *rect, TextureBag &) override;
  void Cycle() override;
};


#endif //R_TYPE_GRAPHICTENTACLEBOSS_HPP
