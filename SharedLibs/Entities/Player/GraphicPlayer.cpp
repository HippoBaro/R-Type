//
// Created by hippolyteb on 11/29/16.
//

#include <Entities/Trait.hpp>
#include "GraphicPlayer.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicPlayer)
#endif

GraphicPlayer::GraphicPlayer(const std::initializer_list<void *> init) : Player(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicPlayer::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    auto texture = bag.getTexture("medias/images/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("medias/images/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));
        texture = bag.AddTexture("medias/images/r-typesheet1.png", sf::IntRect(101, 3, 32, 14), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect->draw(sprite);
}

void GraphicPlayer::Cycle() {
    Player::Cycle();
}

bool GraphicPlayer::NeedRedraw() {
    return false;
}
