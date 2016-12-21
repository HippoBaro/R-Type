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
  if (!isTextureSetInit) {
    isTextureSetInit = true;

    std::vector<sf::IntRect> framePos;
    framePos.push_back(sf::IntRect(256 * 1, 142 * 0, 256, 142));
    framePos.push_back(sf::IntRect(256 * 0, 142 * 0, 256, 142));
    framePos.push_back(sf::IntRect(256 * 1, 142 * 1, 256, 142));
    framePos.push_back(sf::IntRect(256 * 0, 142 * 1, 256, 142));
    framePos.push_back(sf::IntRect(256 * 1, 142 * 2, 256, 142));
    framePos.push_back(sf::IntRect(256 * 0, 142 * 2, 256, 142));
    framePos.push_back(sf::IntRect(256 * 1, 142 * 3, 256, 142));
    framePos.push_back(sf::IntRect(256 * 0, 142 * 3, 256, 142));
    this->setAnimation("medias/images/r-typesheet34.png", framePos, bag, 1000);
  }
  this->updateAnimation(rect, bag);
}

bool GraphicDeathStar::NeedRedraw(){
    return false;
}

void GraphicDeathStar::Cycle() {
    DeathStar::Cycle();
}
