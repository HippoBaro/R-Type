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
        framePos.push_back(sf::IntRect(0, 0, 426, 240));
        framePos.push_back(sf::IntRect(10, 0, 436, 240));
        framePos.push_back(sf::IntRect(20, 0, 446, 240));
        framePos.push_back(sf::IntRect(30, 0, 456, 240));
        framePos.push_back(sf::IntRect(40, 0, 466, 240));
        framePos.push_back(sf::IntRect(50, 0, 476, 240));
        framePos.push_back(sf::IntRect(60, 0, 486, 240));
        framePos.push_back(sf::IntRect(70, 0, 496, 240));
        framePos.push_back(sf::IntRect(80, 0, 506, 240));
        framePos.push_back(sf::IntRect(90, 0, 516, 240));
        framePos.push_back(sf::IntRect(100, 0, 526, 240));
        framePos.push_back(sf::IntRect(110, 0, 536, 240));
        framePos.push_back(sf::IntRect(120, 0, 546, 240));
        framePos.push_back(sf::IntRect(130, 0, 556, 240));
        framePos.push_back(sf::IntRect(140, 0, 566, 240));
        framePos.push_back(sf::IntRect(150, 0, 576, 240));
        setAnimation("medias/images/scrolling.jpg", framePos, bag);
        setLoopDuration(3500);
        setLoopBackAndForth(false);
        setScale(sf::Vector2f(3.0f, 3.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicBackground::Cycle() {
    Background::Cycle();
}
