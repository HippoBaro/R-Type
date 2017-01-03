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

        for (int i = 0; i < 288; ++i) {
            framePos.push_back(sf::IntRect(0 + (2 * i), 0, 576 + (2 * i), 240));
        }

        setAnimation("medias/images/scrolling.jpg", framePos, bag);
        setLoopDuration(7000);
        setLoopBackAndForth(false);
        setScale(sf::Vector2f(2.0f, 3.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicBackground::Cycle() {
    Background::Cycle();
}
