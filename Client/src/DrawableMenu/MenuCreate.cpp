//
// Created by pasteu_e on 10/12/16.
//

#include "DrawableMenu/MenuCreate.hpp"
#include <Messages/MenuStateUpdateMessage.hpp>

MenuCreate::MenuCreate(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuMap[1] = std::make_pair(false, "Ready");
    _menuName = "Create";
    _menuType = HORIZONTAL;
    _textToWrite = "         Waiting";
    _eventListener = std::unique_ptr<RType::EventListener>(new RType::EventListener(_eventManager));
    _eventListener->Subscribe<void, MenuStateUpdateMessage>(MenuStateUpdateMessage::EventType, [&](void *sender, MenuStateUpdateMessage *message) {
        _textToWrite = "         Waiting\n";
        for (const auto &i : message->getPlayers()) {
            _textToWrite += "Player ";
            _textToWrite += (char) (i.GetId() + 48);
            if (i.isReady())
                _textToWrite += "  READY";
            else
                _textToWrite += "  NOT READY";
            _textToWrite += "\n";
        }
    });
}

void MenuCreate::specialDrawing(sf::RenderTexture &context, sf::Text &text) {
    text.setFillColor(sf::Color::White);
    text.setPosition(context.getSize().x / 4, context.getSize().y / 4);
    text.setString(_textToWrite);
    context.draw(text);
}
