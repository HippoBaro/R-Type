//
// Created by pasteu_e on 10/12/16.
//

#include "DrawableMenu/MenuCreate.hpp"
#include <Messages/MenuStateUpdateMessage.hpp.hpp>

MenuCreate::MenuCreate(std::shared_ptr<RType::EventManager> &eventManager) {
    _eventManager = eventManager;
    _menuMap[0] = std::make_pair(true, "Back");
    _menuName = "Create";
    _menuType = HORIZONTAL;
    _textToWrite = "Waiting";

    auto sub = RType::EventListener(_eventManager);

    sub.Subscribe<void, MenuStateUpdateMessage>(MenuStateUpdateMessage::EventType, [&](void *sender, MenuStateUpdateMessage *message) {
        std::vector<PlayerRef> players = message->GetPlayers();
        _textToWrite = "Waiting\n";
        for (auto const &player : players) {
            _textToWrite += "Player ";
            _textToWrite += (player.GetId() + 48);
            if (player.IsReady())
                _textToWrite += "\tReady";
            else if (!player.IsReady())
                _textToWrite += "\tNot Ready";
            _textToWrite += "\n";
        }
        });
}

void MenuCreate::specialDrawing(sf::RenderTexture &context, sf::Text &text) {
    text.setFillColor(sf::Color::White);
    text.setPosition(context.getSize().x / 2 - ((50 * 7) / 3), context.getSize().y / 4);
    text.setString(_textToWrite);
    context.draw(text);
}
