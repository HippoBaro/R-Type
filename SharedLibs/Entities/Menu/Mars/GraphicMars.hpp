//
// Created by pasteu_e on 07/12/16.
//

#ifndef R_TYPE_DRAWABLEPLANET_HPP
#define R_TYPE_DRAWABLEPLANET_HPP

#include <IDrawable.hpp>
#include "Mars.hpp"

class GraphicMars : public Mars, public IDrawable {

public:
    GraphicMars(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;


    virtual bool NeedRedraw() override final;

    void Cycle() override;
};

#endif //R_TYPE_DRAWABLEPLANET_HPP
