//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_IDRAWABLE_HPP
#define R_TYPE_IDRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <vec2.hpp>

class IDrawable {
public:
    virtual ~IDrawable() {}

public:
    virtual void Draw(sf::RenderTexture &rect) = 0;
    virtual vec2<float> GetRenderRect() = 0;
    virtual vec2<float> GetPosition() = 0;
};

#endif //R_TYPE_IDRAWABLE_HPP
