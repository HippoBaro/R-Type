//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEGAMECONTEXT_HPP
#define R_TYPE_RTYPEGAMECONTEXT_HPP


#include <SFML/Graphics/RenderTexture.hpp>
#include "IRtypeDrawingContext.hpp"
#include "../../Shared/EntityPool/EntityPool.hpp"

class RTypeGameContext : public IRtypeDrawingContext{
private:
    EntityPool _pool = EntityPool();
public:
    RTypeGameContext();
    void Draw(sf::RenderTexture &) override final;
};


#endif //R_TYPE_RTYPEGAMECONTEXT_HPP
