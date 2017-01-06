//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_DRAWABLEBIGPROJECTILE_HPP
#define R_TYPE_DRAWABLEBIGPROJECTILE_HPP


#include <IDrawable.hpp>
#include <AAnimatable.hpp>
#include "BigProjectile.hpp"

class DrawableBigProjectile : public BigProjectile, public AAnimatable {
public:
    DrawableBigProjectile(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_DRAWABLEBIGPROJECTILE_HPP
