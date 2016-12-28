//
// Created by pasteu_e on 08/12/16.
//

#include <Messages/ClientWaitForServerMessage.hpp>
#include <Messages/MenuStateUpdateMessage.hpp>
#include "DrawableMenu/ADrawableMenu.hpp"

ADrawableMenu::ADrawableMenu() {
    _move[USER_UP] = std::bind(&ADrawableMenu::moveUp, this);
    _move[USER_DOWN] = std::bind(&ADrawableMenu::moveDown, this);
    _move[USER_LEFT] = std::bind(&ADrawableMenu::moveLeft, this);
    _move[USER_RIGHT] = std::bind(&ADrawableMenu::moveRight, this);
}

ADrawableMenu::~ADrawableMenu() {}

std::string ADrawableMenu::getSelection() {
    for (auto &elem : _menuMap) {
        if (elem.second.first)
            return elem.second.second;
    }
    return std::string();
}

bool ADrawableMenu::isCreateOrJoin(std::unique_ptr<ADrawableMenu> &elem) {
    //Si jamais l'utilistateur n'entre pas de ChannelName alors on l'empeche de passer a la suite
    if (elem->_menuName == "Create" || elem->_menuName == "Join") {
        if (getChannelName() == "")
            return false;
        if (elem->_menuName == "Create")
            _eventManager->Emit(ClientWaitForServerMessage::EventType, new ClientWaitForServerMessage(USER_CREATE, getChannelName()), nullptr);
        else if (elem->_menuName == "Join")
            _eventManager->Emit(ClientWaitForServerMessage::EventType, new ClientWaitForServerMessage(USER_JOIN, getChannelName()), nullptr);
    }
    return true;
}

void ADrawableMenu::checkIfUserStopWaiting() {
    //Si jamais l'utilistateur quitte l'écran Waiting, alors on envoie un signal
    if ((_menuName == "Create" || _menuName == "Join") && getSelection() == "Back") {
        _eventManager->Emit(MenuStateUpdateMessage::EventType, new MenuStateUpdateMessage(), nullptr);
        _eventManager->Emit(ClientWaitForServerMessage::EventType, new ClientWaitForServerMessage(USER_QUIT), nullptr);
    }
}

bool ADrawableMenu::checkIfUserIsReady() {
    if (getSelection() == "Ready") {
        _eventManager->Emit(ClientWaitForServerMessage::EventType, new ClientWaitForServerMessage(USER_READY), nullptr);
        return true;
    }
    return false;
}

void ADrawableMenu::moveUp() {
    if (_canMove && _menuType == VERTICAL) {
        for (auto &elem : _menuMap) {
            if (elem.second.first && elem.first > 0) {
                elem.second.first = !elem.second.first;
                _menuMap[elem.first - 1] = std::make_pair(!_menuMap[elem.first - 1].first, _menuMap[elem.first - 1].second);
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "medias/sounds/changeMenu.ogg"), this);
                break;
            }
        }
    }
}

void ADrawableMenu::moveDown() {
    if (_canMove && _menuType == VERTICAL) {
        for (auto &elem : _menuMap) {
            if (elem.second.first && elem.first < _menuMap.size() - 1) {
                elem.second.first = !elem.second.first;
                _menuMap[elem.first + 1] = std::make_pair(!_menuMap[elem.first + 1].first, _menuMap[elem.first + 1].second);
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "medias/sounds/changeMenu.ogg"), this);
                break;
            }
        }
    }
}

void ADrawableMenu::moveRight() {
    if (_canMove && _menuType == HORIZONTAL) {
        for (auto &elem : _menuMap) {
            if (elem.second.first && elem.first < _menuMap.size() - 1) {
                elem.second.first = !elem.second.first;
                _menuMap[elem.first + 1] = std::make_pair(!_menuMap[elem.first + 1].first, _menuMap[elem.first + 1].second);
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "medias/sounds/changeMenu.ogg"), this);
                break;
            }
        }
    }
}

void ADrawableMenu::moveLeft() {
    if (_canMove && _menuType == HORIZONTAL) {
        for (auto &elem : _menuMap) {
            if (elem.second.first && elem.first > 0) {
                elem.second.first = !elem.second.first;
                _menuMap[elem.first - 1] = std::make_pair(!_menuMap[elem.first - 1].first, _menuMap[elem.first - 1].second);
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "medias/sounds/changeMenu.ogg"), this);
                break;
            }
        }
    }
}

void ADrawableMenu::changeTextColor(std::pair<const unsigned int, std::pair<bool, std::string>> &elem, sf::Text &text) {
    if (elem.second.first)
        text.setFillColor(sf::Color::Red);
    else
        text.setFillColor(sf::Color::White);
}

void ADrawableMenu::moveSelection(UserEventType type) {
    if (_active) {
        _move[type]();
    }
}

bool ADrawableMenu::moveInSubMenu(std::vector<std::unique_ptr<ADrawableMenu>> &allMenu) {
    if (_active) {
        checkIfUserStopWaiting();
        bool cond = checkIfUserIsReady();
        for (auto &&elem : allMenu) {
            if (elem->_menuName == getSelection()) {
                if (!isCreateOrJoin(elem))
                    return false;
                elem->_active = true;
                _active = false;
                _eventManager->Emit(SoundSystemMessage::EventType, new SoundSystemMessage(PLAY_SOUND, "medias/sounds/menuValidate.ogg"), nullptr);
                return true;
            }
        }
        if (!cond)
            _eventManager->Emit(UserInputMessage::EventType, new UserInputMessage(CLOSE_WINDOWS), nullptr);
    }
    return false;
}

void ADrawableMenu::Draw(sf::RenderTexture &context, sf::Text &text) {
    if (_active) {
        float x = (context.getSize().x / 2.65f);
        float y = (context.getSize().y / 3.f);
        for (auto &elem : _menuMap) {
            changeTextColor(elem, text);
            text.setString(elem.second.second);
            if (_menuType == VERTICAL) {
                text.setPosition(150, y);
                y += 50;
            } else if (_menuType == HORIZONTAL) {
                text.setPosition(x, 510);
                x += (elem.second.second.size() * 50);
            }
            context.draw(text);
        }
        specialDrawing(context, text);
    }
}

const std::string ADrawableMenu::getChannelName() {
    return std::string();
}

void ADrawableMenu::specialDrawing(sf::RenderTexture &context, sf::Text &text) {

}