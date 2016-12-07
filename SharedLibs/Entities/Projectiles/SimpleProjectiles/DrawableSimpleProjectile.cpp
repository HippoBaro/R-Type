//
// Created by hippolyteb on 12/5/16.
//

#include "DrawableSimpleProjectile.hpp"

DrawableSimpleProjectile::DrawableSimpleProjectile(const std::initializer_list<void *> init) : SimpleProjectile(init) {}

void DrawableSimpleProjectile::Draw(sf::RenderTexture &rect) {
    sf::Texture texture;
    rect.clear(sf::Color::Transparent);
    texture.loadFromFile("sprites/r-typesheet1.png", sf::IntRect(257, 109, 16, 8));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect.draw(sprite);
}

vec2<float> DrawableSimpleProjectile::GetRenderRect() {
    return vec2<float>(16 * 5, 8 * 5);
}

vec2<float> DrawableSimpleProjectile::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

void DrawableSimpleProjectile::Cycle() {
    SimpleProjectile::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableSimpleProjectile)