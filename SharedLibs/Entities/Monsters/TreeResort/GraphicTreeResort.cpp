//
// Created by barre_k
//

#include "GraphicTreeResort.hpp"

#define H 130
#define L 64

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
        framePos.push_back(sf::IntRect(L * 0, 0, L, H));
        framePos.push_back(sf::IntRect(L * 1, 0, L, H));
        framePos.push_back(sf::IntRect(L * 2, 0, L, H));
        framePos.push_back(sf::IntRect(L * 3, 0, L, H));
        framePos.push_back(sf::IntRect(L * 4, 0, L, H));
        framePos.push_back(sf::IntRect(L * 5, 0, L, H));
        framePos.push_back(sf::IntRect(L * 6, 0, L, H));
        framePos.push_back(sf::IntRect(L * 7, 0, L, H));
        setAnimation("medias/images/r-typesheet17.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicTreeResort::Cycle() {
    TreeResort::Cycle();
}
