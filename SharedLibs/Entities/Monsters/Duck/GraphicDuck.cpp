//
// Created by barre_k
//

#include "GraphicDuck.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicDuck)
#endif

GraphicDuck::GraphicDuck(const std::initializer_list<void *> init) :
        Duck(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
}

void GraphicDuck::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(_width * 0, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 1, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 2, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 3, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 4, 0, _width, _height));
        framePos.push_back(sf::IntRect(_width * 5, 0, _width, _height));
        setAnimation("medias/images/r-typesheet11.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicDuck::Cycle() {
    Duck::Cycle();
}
