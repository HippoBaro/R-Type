//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_IDRAWABLE_HPP
#define R_TYPE_IDRAWABLE_HPP

#include <vec2.hpp>
#include <SFML/Graphics.hpp>

class IDrawable {
public:
    virtual ~IDrawable() {}

public:
    virtual void Draw(sf::RenderTexture &rect) = 0;
    virtual vec2<int> GetRenderRect() = 0;
    virtual vec2<int> GetPosition() = 0;
};

#endif //R_TYPE_IDRAWABLE_HPP
