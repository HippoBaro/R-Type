//
// Created by barre_k
//

#include "GraphicSpaceShip.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicTreeResort)
#endif

GraphicTreeResort::GraphicTreeResort(const std::initializer_list<void *> init) :
        SpaceShip(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
}

void GraphicTreeResort::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(_width * 0, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 1, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 2, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 3, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 4, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 5, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 6, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 7, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 8, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 9, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 10, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 11, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 12, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 13, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 14, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 15, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 16, 0, _width, _height));
        setAnimation("medias/images/r-typesheet5.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicTreeResort::Cycle() {
    SpaceShip::Cycle();
}
