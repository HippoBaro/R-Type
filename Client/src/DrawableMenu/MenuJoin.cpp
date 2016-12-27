//
// Created by pasteu_e on 10/12/16.
//

#include <Messages/MenuStateUpdateMessage.hpp.hpp>
#include "DrawableMenu/MenuJoin.hpp"

MenuJoin::MenuJoin(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuMap[1] = std::make_pair(false, "Ready");
    _menuName = "Join";
    _menuType = HORIZONTAL;
    _textToWrite = "Waiting";
    _eventListener = std::unique_ptr<RType::EventListener>(new RType::EventListener(_eventManager));

    _eventListener->Subscribe<void, MenuStateUpdateMessage>(MenuStateUpdateMessage::EventType, [&](void *sender, MenuStateUpdateMessage *message) {
        //_textToWrite = message->GetTextToWrite();
    });
}

void MenuJoin::specialDrawing(sf::RenderTexture &context, sf::Text &text) {
    text.setFillColor(sf::Color::White);
    text.setPosition(context.getSize().x / 2 - ((50 * 7) / 3), context.getSize().y / 4);
    text.setString(_textToWrite);
    context.draw(text);
}
