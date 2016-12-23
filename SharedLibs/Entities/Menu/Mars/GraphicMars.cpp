//
// Created by pasteu_e on 07/12/16.
//

#include "GraphicMars.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicMars)
#endif

GraphicMars::GraphicMars(const std::initializer_list<void *> init) : Mars(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicMars::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("medias/images/mars.png", sf::IntRect(0, 0, 500, 500));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("medias/images/mars.png", sf::IntRect(0, 0, 500, 500));
        texture = bag.AddTexture("medias/images/mars.png", sf::IntRect(0, 0, 500, 500), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));
    rect->draw(sprite);
}

bool GraphicMars::DidChangeDraw(){
    return false;
}

void GraphicMars::Cycle() {
    Mars::Cycle();
}
