//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEMENUCONTEXT_HPP
#define R_TYPE_RTYPEMENUCONTEXT_HPP


#include "IRTypeDrawingContext.hpp"

class RTypeMenuContext : public IRTypeDrawingContext {
public:
    void Draw(sf::RenderTexture &, TextureBag &) override final;
};


#endif //R_TYPE_RTYPEMENUCONTEXT_HPP
