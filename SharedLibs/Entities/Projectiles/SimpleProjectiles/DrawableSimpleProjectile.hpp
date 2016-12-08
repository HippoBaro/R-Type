//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_DRAWABLESIMPLEPROJECTILE_HPP
#define R_TYPE_DRAWABLESIMPLEPROJECTILE_HPP


#include <IDrawable.hpp>
#include "SimpleProjectile.hpp"

class DrawableSimpleProjectile : public SimpleProjectile, public IDrawable  {
public:
    DrawableSimpleProjectile(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

public:
    virtual ~DrawableSimpleProjectile();

private:
    void Cycle() override;
};


#endif //R_TYPE_DRAWABLESIMPLEPROJECTILE_HPP
