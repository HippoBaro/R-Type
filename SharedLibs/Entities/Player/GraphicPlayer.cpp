//
// Created by hippolyteb on 11/29/16.
//

#include "GraphicPlayer.hpp"

GraphicPlayer::GraphicPlayer(Timer *timer) : Player(timer) {}

void GraphicPlayer::Draw(sf::RenderTexture &rect) {
    sf::Texture texture;
    rect.clear(sf::Color::Transparent);
    texture.loadFromFile("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect.draw(sprite);
}

vec2<int> GraphicPlayer::GetRenderRect() {
    return vec2<int>(32 * 5, 14 * 5);
}

vec2<int> GraphicPlayer::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicPlayer)