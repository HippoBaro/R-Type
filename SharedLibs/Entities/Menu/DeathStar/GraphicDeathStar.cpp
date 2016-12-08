//
// Created by pasteu_e on 07/12/16.
//

#include "GraphicDeathStar.hpp"

GraphicDeathStar::GraphicDeathStar(const std::initializer_list<void *> init) : DeathStar(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicDeathStar::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("sprites/deathStar.png", sf::IntRect(0, 0, 500, 500));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("sprites/deathStar.png", sf::IntRect(0, 0, 500, 500));
        texture = bag.AddTexture("sprites/deathStar.png", sf::IntRect(0, 0, 500, 500), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect->draw(sprite);
}

vec2<float> GraphicDeathStar::GetRenderRect() {
    return vec2<float>(500 * 0.3, 500 * 0.3);
}

vec2<float> GraphicDeathStar::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

void GraphicDeathStar::Cycle() {
    DeathStar::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicDeathStar)