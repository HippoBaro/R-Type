//
// Created by aguado_e on 12/22/16.
//

#include "GraphicTentacleBoss.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicTentacleBoss)
#endif

GraphicTentacleBoss::GraphicTentacleBoss(const std::initializer_list<void *> init) :
        TentacleBoss(init),
        AAnimable()
{
    this->RegisterTrait(Trait::Drawable);
}

void GraphicTentacleBoss::Draw(sf::RenderTexture *rect, TextureBag &bag) {
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
        this->setAnimation("medias/images/r-typesheet34.png", framePos, bag);
        this->setLoopDuration(1500);
        this->setTimeoutAtEnd(1000);
        this->setScale(sf::Vector2f(4.0f, 4.0f));
    }
    this->updateAnimation(rect, bag);
}

void GraphicTentacleBoss::Cycle() {
    TentacleBoss::Cycle();
}
