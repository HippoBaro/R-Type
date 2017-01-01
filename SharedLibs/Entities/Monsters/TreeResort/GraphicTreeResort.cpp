//
// Created by barre_k
//

#include "GraphicTreeResort.hpp"

static constexpr int _height = 130;
static constexpr int _width = 64;

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicTreeResort)
#endif

GraphicTreeResort::GraphicTreeResort(const std::initializer_list<void *> init) :
        TreeResort(init),
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
        setAnimation("medias/images/r-typesheet17.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicTreeResort::Cycle() {
    TreeResort::Cycle();
}
