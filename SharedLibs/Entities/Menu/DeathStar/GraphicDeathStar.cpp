//
// Created by pasteu_e on 07/12/16.
//

#include "GraphicDeathStar.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicDeathStar)
#endif

GraphicDeathStar::GraphicDeathStar(const std::initializer_list<void *> init) : DeathStar(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicDeathStar::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("medias/images/deathStar.png", sf::IntRect(0, 0, 500, 500));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("medias/images/deathStar.png", sf::IntRect(0, 0, 500, 500));
        texture = bag.AddTexture("medias/images/deathStar.png", sf::IntRect(0, 0, 500, 500), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect->draw(sprite);
}

bool GraphicDeathStar::NeedRedraw(){
    return false;
}

void GraphicDeathStar::Cycle() {
    DeathStar::Cycle();
}