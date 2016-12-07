//
// Created by hippolyteb on 11/29/16.
//

#include "GraphicDummyMonster.hpp"

GrahicDummyMonster::GrahicDummyMonster(const std::initializer_list<void *> init) : DummyMonster(init) {}

void GrahicDummyMonster::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getSprite("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));
        texture = bag.AddSprite("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect->draw(sprite);
}

vec2<float> GrahicDummyMonster::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> GrahicDummyMonster::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

void GrahicDummyMonster::Cycle() {
    DummyMonster::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GrahicDummyMonster)