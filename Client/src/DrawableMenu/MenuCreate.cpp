//
// Created by pasteu_e on 10/12/16.
//

#include "DrawableMenu/MenuCreate.hpp"

MenuCreate::MenuCreate(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuName = "Create";
    _menuType = HORIZONTAL;
}

void MenuCreate::specialDrawing(sf::RenderTexture &context, sf::Text &text) {
    text.setFillColor(sf::Color::White);
    text.setPosition(context.getSize().x / 2 - ((50 * 7) / 3), context.getSize().y / 4);
    text.setString("Waiting");
    context.draw(text);
}
