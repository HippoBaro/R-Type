//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_IRTYPEDRAWINGCONTEXT_HPP
#define R_TYPE_IRTYPEDRAWINGCONTEXT_HPP

#include <SFML/Graphics.hpp>

class IRtypeDrawingContext {
public:
    virtual void Draw(sf::RenderTexture &) = 0;
    virtual ~IRtypeDrawingContext() {};
};


#endif //R_TYPE_IRTYPEDRAWINGCONTEXT_HPP
