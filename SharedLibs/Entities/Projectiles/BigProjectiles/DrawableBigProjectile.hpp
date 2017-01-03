//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_DRAWABLEBIGPROJECTILE_HPP
#define R_TYPE_DRAWABLEBIGPROJECTILE_HPP


#include <IDrawable.hpp>
#include "BigProjectile.hpp"

class DrawableBigProjectile : public BigProjectile, public IDrawable  {
public:
    DrawableBigProjectile(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;


    virtual bool NeedRedraw() override ;

public:
    virtual ~DrawableBigProjectile();

private:
    void Cycle() override;
};


#endif //R_TYPE_DRAWABLEBIGPROJECTILE_HPP
