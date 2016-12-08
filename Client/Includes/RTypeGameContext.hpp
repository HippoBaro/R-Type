//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEGAMECONTEXT_HPP
#define R_TYPE_RTYPEGAMECONTEXT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include "IRtypeDrawingContext.hpp"
#include "ClientEntityPool.hpp"

class RTypeGameContext : public IRtypeDrawingContext{
private:
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<ClientEntityPool> _pool = nullptr;
public:
    RTypeGameContext();
    void Draw(sf::RenderTexture &, TextureBag &) override final;
};


#endif //R_TYPE_RTYPEGAMECONTEXT_HPP
