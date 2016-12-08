//
// Created by pasteu_e on 08/12/16.
//

#include "GraphicShip.hpp"

GraphicShip::GraphicShip(const std::initializer_list<void *> init) : Ship(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicShip::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("sprites/starwarsShip.png", sf::IntRect(0, 0, 390, 390));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("sprites/starwarsShip.png", sf::IntRect(0, 0, 390, 390));
        texture = bag.AddTexture("sprites/starwarsShip.png", sf::IntRect(0, 0, 390, 390), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect->draw(sprite);
}

vec2<float> GraphicShip::GetRenderRect() {
    return vec2<float>(500 * 0.3, 500 * 0.3);
}

vec2<float> GraphicShip::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

void GraphicShip::Cycle() {
    Ship::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicShip)