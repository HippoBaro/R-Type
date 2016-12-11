//
// Created by hippolyteb on 11/29/16.
//

#include <Entities/Trait.hpp>
#include "GraphicPlayer.hpp"

GraphicPlayer::GraphicPlayer(const std::initializer_list<void *> init) : Player(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicPlayer::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));
        texture = bag.AddTexture("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect->draw(sprite);
}

vec2<float> GraphicPlayer::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> GraphicPlayer::GetPosition() {
    //auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    //return pos;
    return vec2<float>(2, 2);
}

void GraphicPlayer::Cycle() {
    Player::Cycle();
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicPlayer)