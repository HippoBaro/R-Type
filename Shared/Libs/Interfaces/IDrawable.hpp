//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_IDRAWABLE_HPP
#define R_TYPE_IDRAWABLE_HPP

#include <SFML/Graphics.hpp>

class IDrawable {
public:
    IDrawable(Entity *self) {
        self->RegisterTrait(Trait::Drawable);
    }

    virtual void Draw(sf::RenderTexture &rect) = 0;
    virtual vec2<unsigned int> GetRenderRect() = 0;
    virtual vec2<unsigned int> GetPosition() = 0;
};

#endif //R_TYPE_IDRAWABLE_HPP
