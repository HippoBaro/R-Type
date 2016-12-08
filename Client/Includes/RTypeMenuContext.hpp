//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEMENUCONTEXT_HPP
#define R_TYPE_RTYPEMENUCONTEXT_HPP


#include "IRTypeDrawingContext.hpp"
#include "ClientEntityPool.hpp"

class RTypeMenuContext : public IRTypeDrawingContext {
private:
    ClientEntityPool _pool = ClientEntityPool();
    sf::Texture _backgroundTexture;
    sf::Sprite _background;
    sf::Font _font;
    sf::Text _text;
    std::map<std::string, bool> _menuRoot;

private:
    void DrawMenu(sf::RenderTexture &, std::map<std::string, bool> &);

public:
    RTypeMenuContext();

    void Draw(sf::RenderTexture &) override final;
};


#endif //R_TYPE_RTYPEMENUCONTEXT_HPP
