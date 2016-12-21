//
// Created by pasteu_e on 07/12/16.
//

#include "GraphicDeathStar.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicDeathStar)
#endif

GraphicDeathStar::GraphicDeathStar(const std::initializer_list<void *> init) : DeathStar(init), AAnimable() {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicDeathStar::Draw(sf::RenderTexture *rect, TextureBag &bag) {

//  auto texture = bag.getTexture("medias/images/deathStar.png", sf::IntRect(0, 0, 500, 500));

  if (!isTextureSetInit) {
    isTextureSetInit = true;
    std::vector<sf::IntRect> framePos;
    framePos.push_back(sf::IntRect(0, 0, 150, 150));
    framePos.push_back(sf::IntRect(150, 150, 150, 150));
    this->setAnimation("medias/images/deathStar.png", framePos, bag);
  }

  this->updateAnimation(rect, bag);
}

bool GraphicDeathStar::NeedRedraw(){
    return false;
}

void GraphicDeathStar::Cycle() {
    DeathStar::Cycle();
}
