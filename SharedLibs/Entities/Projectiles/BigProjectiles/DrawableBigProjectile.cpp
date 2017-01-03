//
// Created by hippolyteb on 12/5/16.
//

#include <iostream>
#include <Messages/ProjectilePositionChangedMessage.hpp>
#include "DrawableBigProjectile.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableBigProjectile)
#endif

DrawableBigProjectile::DrawableBigProjectile(const std::initializer_list<void *> init) : BigProjectile(init) {
    this->RegisterTrait(Trait::Drawable);
}

void DrawableBigProjectile::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    auto texture = bag.getTexture("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        auto newtexture = std::make_shared<sf::Texture>();
        newtexture->loadFromFile("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8));
        texture = bag.AddTexture("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8), newtexture);
    }
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    rect->draw(sprite);
}

void DrawableBigProjectile::Cycle() {
    BigProjectile::Cycle();
}

DrawableBigProjectile::~DrawableBigProjectile() {}

bool DrawableBigProjectile::NeedRedraw() {
    return false;
}
