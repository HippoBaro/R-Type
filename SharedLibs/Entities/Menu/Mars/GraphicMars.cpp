//
// Created by pasteu_e on 07/12/16.
//

#include "GraphicMars.hpp"

GraphicMars::GraphicMars(const std::initializer_list<void *> init) : Mars(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicMars::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("sprites/mars.png", sf::IntRect(0, 0, 500, 500));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("sprites/mars.png", sf::IntRect(0, 0, 500, 500));
        texture = bag.AddTexture("sprites/mars.png", sf::IntRect(0, 0, 500, 500), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));
    rect->draw(sprite);
}

vec2<float> GraphicMars::GetRenderRect() {
    return vec2<float>(500 * 0.6, 500 * 0.6);
}

vec2<float> GraphicMars::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void GraphicMars::Cycle() {
    Mars::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicMars)