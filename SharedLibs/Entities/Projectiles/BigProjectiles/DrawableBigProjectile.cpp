//
// Created by hippolyteb on 12/5/16.
//

#include <iostream>
#include <Messages/ProjectilePositionChangedMessage.hpp>
#include "DrawableBigProjectile.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableBigProjectile)
#endif

DrawableBigProjectile::DrawableBigProjectile(const std::initializer_list<void *> init) :
        BigProjectile(init),
        AAnimatable()
{
    this->RegisterTrait(Trait::Drawable);
}

void DrawableBigProjectile::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(0, 0, 65, 14));
        framePos.push_back(sf::IntRect(65, 0, 65, 14));
        setAnimation("medias/images/bigprojectile.png", framePos, bag);
        setLoopDuration(100);
        setScale(sf::Vector2f(2.0f, 2.0f));
    }
    updateAnimation(rect, bag);
}

void DrawableBigProjectile::Cycle() {
    BigProjectile::Cycle();
}
