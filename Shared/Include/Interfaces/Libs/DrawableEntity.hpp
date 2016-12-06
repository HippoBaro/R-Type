//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_DRAWABLEENTITY_HPP
#define R_TYPE_DRAWABLEENTITY_HPP

#include "Entity.hpp"
#include <IDrawable.hpp>

class DrawableEntity : public Entity, public IDrawable {
public:
    DrawableEntity() {
        this->RegisterTrait(Trait::Drawable);
    }
};

#endif //R_TYPE_DRAWABLEENTITY_HPP
