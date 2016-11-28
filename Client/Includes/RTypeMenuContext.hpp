//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEMENUCONTEXT_HPP
#define R_TYPE_RTYPEMENUCONTEXT_HPP


#include "IRtypeDrawingContext.hpp"

class RTypeMenuContext : public IRtypeDrawingContext {
public:
    void Draw(sf::RenderTexture &) override final;
};


#endif //R_TYPE_RTYPEMENUCONTEXT_HPP
