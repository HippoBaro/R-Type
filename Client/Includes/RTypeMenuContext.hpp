//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEMENUCONTEXT_HPP
#define R_TYPE_RTYPEMENUCONTEXT_HPP


#include "IRTypeDrawingContext.hpp"
#include "ClientEntityPool.hpp"
#include <Messages/UserInputMessage.hpp>
#include "DrawableMenu/ADrawableMenu.hpp"
#include <vector>

class RTypeMenuContext : public IRTypeDrawingContext {
private:
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<ClientEntityPool> _pool = nullptr;
    sf::Texture _backgroundTexture = sf::Texture();
    sf::Sprite _background = sf::Sprite();
    sf::Font _font = sf::Font();
    sf::Text _text = sf::Text();

    std::vector<std::unique_ptr<ADrawableMenu>> _menu {};

    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;

private:
    void DrawMenu(sf::RenderTexture &context);

public:
    RTypeMenuContext(std::shared_ptr<RType::EventManager> eventManager);
    void Draw(sf::RenderTexture &, TextureBag &) override final;
};


#endif //R_TYPE_RTYPEMENUCONTEXT_HPP
