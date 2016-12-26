//
// Created by aguado_e on 12/22/16.
//

#ifndef R_TYPE_GRAPHICORBMONSTER_HPP
#define R_TYPE_GRAPHICORBMONSTER_HPP

#include <AAnimable.hpp>
#include <TextureBag.hpp>
#include "OrbMonster.hpp"

class GraphicOrbMonster : public OrbMonster, public AAnimable {

public:
  GraphicOrbMonster(const std::initializer_list<void *> init);

public:
  void Draw(sf::RenderTexture *rect, TextureBag &) override;
  void Cycle() override;
};


#endif //R_TYPE_GRAPHICORBMONSTER_HPP
