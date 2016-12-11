//
// Created by hippolyteb on 12/5/16.
//

#include <iostream>
#include <Messages/ProjectilePositionChangedMessage.hpp>
#include "DrawableSimpleProjectile.hpp"

DrawableSimpleProjectile::DrawableSimpleProjectile(const std::initializer_list<void *> init) : SimpleProjectile(init) {
    this->RegisterTrait(Trait::Drawable);
}

void DrawableSimpleProjectile::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    auto texture = bag.getTexture("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8));
        texture = bag.AddTexture("medias/images/r-typesheet1.png", sf::IntRect(249, 105, 16, 8), newtexture);
    }
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    //sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect->draw(sprite);
}

vec2<float> DrawableSimpleProjectile::GetRenderRect() {
    return vec2<float>(16, 8);
}

vec2<float> DrawableSimpleProjectile::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void DrawableSimpleProjectile::Cycle() {
    SimpleProjectile::Cycle();
}

DrawableSimpleProjectile::~DrawableSimpleProjectile() {}

RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableSimpleProjectile)