//
// Created by pasteu_e on 27/11/16.
//

#include <vec2.hpp>
#include <Time/Timer.hpp>
#include <SFMLManager.hpp>
#include <Messages/MenuStateUpdateMessage.hpp>
#include "RTypeMenuContext.hpp"
#include "DrawableMenu/MenuCreateRoom.hpp"
#include "DrawableMenu/MenuJoinRoom.hpp"
#include "DrawableMenu/MenuRoot.hpp"
#include "DrawableMenu/MenuSettings.hpp"
#include "DrawableMenu/MenuCreate.hpp"
#include "DrawableMenu/MenuJoin.hpp"
#include "DrawableMenu/MenuMusicVolume.hpp"
#include "DrawableMenu/MenuSoundVolume.hpp"


RTypeMenuContext::RTypeMenuContext(std::shared_ptr<RType::EventManager> &eventManager) : _globalEventManager(eventManager), _globalEventListener(eventManager) {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer, _eventManager);

    auto stratPos = vec2<float>(1500, 100);
    _pool->AddEntity("DeathStar", 1, stratPos, _timer->getCurrent());

    stratPos = vec2<float>(1100, 450);
    _pool->AddEntity("Mars", 2, stratPos, _timer->getCurrent());

    stratPos = vec2<float>(-100, -100);
    _pool->AddEntity("Ship", 3, stratPos, _timer->getCurrent());

    _backgroundTexture.loadFromFile("medias/images/spacebackground.jpg");
    _background.setTexture(_backgroundTexture);
    _font.loadFromFile("medias/fonts/mypdark.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(50);

    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuRoot(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuCreateRoom(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuJoinRoom(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuSettings(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuCreate(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuJoin(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuMusicVolume(_eventManager)));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuSoundVolume(_eventManager)));

    _globalEventListener.Reroute(UserInputMessage::EventType, _eventManager);
    _globalEventListener.Reroute(UserInputEntryMessage::EventType, _eventManager);
    _eventListener.Reroute(SoundSystemMessage::EventType, _globalEventManager);
    _eventListener.Reroute(MenuStateUpdateMessage::EventType, _globalEventManager);

    _eventListener.Subscribe<void, UserInputMessage>(UserInputMessage::EventType, [&](void *, UserInputMessage *message) {
        if (message->ReleasedContainsOnly(USER_UP) || message->ReleasedContainsOnly(USER_DOWN) ||
            message->ReleasedContainsOnly(USER_LEFT) ||
            message->ReleasedContainsOnly(USER_RIGHT)) {
            for (auto &&elem : _menu) {
                elem->moveSelection(message->FirstReleased());
            }
        } else if (message->ReleasedContainsOnly(USER_ENTER)) {
            for (auto &&elem : _menu) {
                if (elem->moveInSubMenu(_menu))
                    break;
            }
        }
    });
}

void RTypeMenuContext::Setup(std::string const &string) {
}

void RTypeMenuContext::ReleaseListener() {
    _globalEventListener.Unsubscribe(UserInputMessage::EventType);
    _globalEventListener.Unsubscribe(UserInputEntryMessage::EventType);
    _eventListener.Unsubscribe(SoundSystemMessage::EventType);
    _eventListener.Unsubscribe(MenuStateUpdateMessage::EventType);
}

void RTypeMenuContext::DrawMenu(sf::RenderTexture &context) {
    for (auto &&elem : _menu) {
        elem->Draw(context, _text);
    }
}

void RTypeMenuContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    //TODO: DIRTY ! We need to find a better solution on OSX for that !
    context.create(1280, 720);
    context.clear(sf::Color::Black);
    context.draw(_background);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    DrawMenu(context);
    context.display();
}
