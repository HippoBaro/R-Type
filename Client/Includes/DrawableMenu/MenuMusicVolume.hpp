//
// Created by pasteu_e on 10/12/16.
//

#ifndef R_TYPE_MENUMUSICVOLUME_HPP
#define R_TYPE_MENUMUSICVOLUME_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuMusicVolume : public ADrawableMenu {
private:
    int _volume = 50;
    RType::EventListener _eventListener;

public:
    MenuMusicVolume(std::shared_ptr<RType::EventManager> &eventManager) : _eventListener(eventManager) {
        _eventManager = eventManager;
        _menuMap[0] = std::make_pair(true, "Back");
        _menuName = "Music Volume";
        _menuType = HORIZONTAL;

        _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
            if (_active) {
                if (message->getEventType() == USER_RIGHT && _volume < 100) {
                    _volume++;
                    _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(_volume, VOLUME_MUSIC), this);
                } else if (message->getEventType() == USER_LEFT && _volume > 0) {
                    _volume--;
                    _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(_volume, VOLUME_MUSIC), this);
                }

            }
        });
    }

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override {
        text.setFillColor(sf::Color::White);
        text.setPosition(context.getSize().x / 2 - ((50 * 12) / 3), context.getSize().y / 4);
        text.setString("Music Volume");
        context.draw(text);
        sf::RectangleShape bar(sf::Vector2f((context.getSize().x / 3) * 2, 2));
        bar.setPosition(sf::Vector2f((context.getSize().x / 2) - ((context.getSize().x / 3)), context.getSize().y / 2.15f));
        context.draw(bar);
        sf::CircleShape vol(10);
        int posX = (context.getSize().x / 2) - ((context.getSize().x / 3));
        posX += (_volume * ((context.getSize().x / 3) * 2) / 100);
        vol.setPosition(sf::Vector2f(posX, context.getSize().y / 2.2f));
        context.draw(vol);
    }
};

#endif //R_TYPE_MENUMUSICVOLUME_HPP
