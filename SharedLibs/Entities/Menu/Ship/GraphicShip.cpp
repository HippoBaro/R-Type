//
// Created by pasteu_e on 08/12/16.
//

#include "GraphicShip.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicShip)
#endif

GraphicShip::GraphicShip(const std::initializer_list<void *> init) : Ship(init) {
    this->RegisterTrait(Trait::Drawable);
}

void GraphicShip::Draw(sf::RenderTexture *rect, TextureBag &bag) {

    auto texture = bag.getTexture("medias/images/starwarsShip.png", sf::IntRect(0, 0, 390, 390));

    rect->clear(sf::Color::Transparent);
    if (texture == nullptr) {
        sf::Texture newtexture;
        newtexture.loadFromFile("medias/images/starwarsShip.png", sf::IntRect(0, 0, 390, 390));
        texture = bag.AddTexture("medias/images/starwarsShip.png", sf::IntRect(0, 0, 390, 390), newtexture);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect->draw(sprite);
}

void GraphicShip::Cycle() {
    Ship::Cycle();
}

bool GraphicShip::NeedRedraw() {
    return false;
}
