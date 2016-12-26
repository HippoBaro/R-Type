//
// Created by aguado_e on 12/22/16.
//

#include <AAnimable.hpp>
#include "GraphicOrbMonster.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicOrbMonster)
#endif

GraphicOrbMonster::GraphicOrbMonster(const std::initializer_list<void *> init) :
        OrbMonster(init),
        AAnimable()
{
    this->RegisterTrait(Trait::Drawable);
}

void GraphicOrbMonster::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        for (uint8_t i = 0 ; i < 12 ; i++)
            framePos.push_back(sf::IntRect(16 * i, 0, 16, 14));
        this->setAnimation("medias/images/OrbMonster.png", framePos, bag, 1200);
    }
    this->updateAnimation(rect, bag);
}

void GraphicOrbMonster::Cycle() {
    OrbMonster::Cycle();
}
