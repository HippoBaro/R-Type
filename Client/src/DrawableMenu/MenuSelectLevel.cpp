//
// Created by Etienne Pasteur on 01/01/2017.
//

#include "DrawableMenu/MenuSelectLevel.hpp"

MenuSelectLevel::MenuSelectLevel(std::shared_ptr<RType::EventManager> &eventManager) : ADrawableInputMenu(eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuMap[1] = std::make_pair(false, "Go");
    _menuName = "Create Room";
    _menuType = HORIZONTAL;
}

void MenuSelectLevel::specialDrawing(sf::RenderTexture &context, sf::Text &text) {
    _frame++;
    if (_frame > 30) {
        _blinkingCursor = !_blinkingCursor;
        if (_blinkingCursor)
            _drawableTextByUser += "_";
        else if (_drawableTextByUser.back() == '_')
            _drawableTextByUser.pop_back();
        _frame = 0;
    }
    text.setFillColor(sf::Color::White);
    text.setPosition(context.getSize().x / 2 - ((50 * 15) / 3), context.getSize().y / 4);
    text.setString("Enter Level Name");
    context.draw(text);
    text.setPosition(context.getSize().x / 2.8f, context.getSize().y / 2.5f);
    text.setString(_drawableTextByUser);
    context.draw(text);
}
