//
// Created by aguado_e on 12/22/16.
//

#include "GraphicBackground.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicBackground)
#endif

GraphicBackground::GraphicBackground(const std::initializer_list<void *> init) :
        Background(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
}

void GraphicBackground::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(256 * 1, 142 * 0, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 0, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 1, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 1, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 2, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 2, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 3, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 3, 256, 142));
        setAnimation("medias/images/r-typesheet34.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicBackground::Cycle() {
    Background::Cycle();
}
