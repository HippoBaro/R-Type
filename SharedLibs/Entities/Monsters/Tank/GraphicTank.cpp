//
// Created by barre_k
//

#include "GraphicTank.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicTank)
#endif

GraphicTank::GraphicTank(const std::initializer_list<void *> init) :
        Tank(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
}

void GraphicTank::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(_width * 0, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 1, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 2, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 3, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 4, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 5, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 6, _height, _width, _height));
        framePos.push_back(sf::IntRect(_width * 7, _height, _width, _height));
        framePos.push_back(sf::IntRect(_width * 8, _height, _width, _height));
        framePos.push_back(sf::IntRect(_width * 9, _height, _width, _height));
        framePos.push_back(sf::IntRect(_width * 10, _height, _width, _height));
        framePos.push_back(sf::IntRect(_width * 11, _height, _width, _height));
        setAnimation("medias/images/r-typesheet12.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicTank::Cycle() {
    Tank::Cycle();
}
