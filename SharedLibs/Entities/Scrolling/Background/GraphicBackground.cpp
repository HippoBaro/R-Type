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

        for (int i = 0; i < 160; ++i) {
            framePos.push_back(sf::IntRect(0 + (i * 2), 0, 320 + (i * 2), 240));
        }

        setAnimation("medias/images/scrolling.jpg", framePos, bag);
        setLoopDuration(5000);
        setLoopBackAndForth(false);
        setScale(sf::Vector2f(4.0f, 3.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicBackground::Cycle() {
    Background::Cycle();
}
