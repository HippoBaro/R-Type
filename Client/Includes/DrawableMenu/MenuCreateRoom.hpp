//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MENUCREATEROOM_HPP
#define R_TYPE_MENUCREATEROOM_HPP

#include "DrawableMenu/ADrawableMenu.hpp"

class MenuCreateRoom : public ADrawableMenu {
private:
    bool _blinkingCursor = true;
    int _frame = 0;
    std::string _drawableTextByUser = "_";
    RType::EventListener _eventListener;

public:
    MenuCreateRoom(std::shared_ptr<RType::EventManager> &eventManager) : _eventListener(eventManager.get()) {
        _eventManager = eventManager;
        _menuMap[0] = std::make_pair(true, "Back");
        _menuMap[1] = std::make_pair(false, "Create");
        _menuName = "Create Room";
        _menuType = HORIZONTAL;

        _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
            if (_active && message->getEventType() == USER_LETTER) {
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "sprites/keyboard_key.ogg"), this);
                if (message->getUserLetter() != '\b') {
                    if (_blinkingCursor) {
                        if (_drawableTextByUser.size() < 12) {
                            _drawableTextByUser.pop_back();
                            _drawableTextByUser += message->getUserLetter();
                            _drawableTextByUser += "_";
                        }
                    } else {
                        if (_drawableTextByUser.size() < 11)
                            _drawableTextByUser += message->getUserLetter();
                    }
                } else if (_drawableTextByUser.size() > 0) {
                    if (_blinkingCursor && _drawableTextByUser.size() > 1) {
                        _drawableTextByUser.pop_back();
                        _drawableTextByUser.pop_back();
                        _drawableTextByUser += "_";
                    } else if (_blinkingCursor) {
                        _drawableTextByUser.pop_back();
                        _drawableTextByUser += "_";
                    } else
                        _drawableTextByUser.pop_back();
                }
            }
        });

    }

    void specialDrawing(sf::RenderTexture &context, sf::Text &text) override {
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
        text.setString("Enter Name Room");
        context.draw(text);
        text.setPosition(context.getSize().x / 2.8f, context.getSize().y / 2.5f);
        text.setString(_drawableTextByUser);
        context.draw(text);
    }

    const std::string getChannelName() override {
        if (_blinkingCursor && !_drawableTextByUser.empty() && _drawableTextByUser.back() == '_')
            _drawableTextByUser.pop_back();
        return _drawableTextByUser;
    }
};


#endif //R_TYPE_MENUCREATEROOM_HPP
