//
// Created by pasteu_e on 27/11/16.
//

#include <vec2.hpp>
#include <Time/Timer.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include <SFMLManager.hpp>
#include "RTypeMenuContext.hpp"
#include "DrawableMenu/MenuCreate.hpp"
#include "DrawableMenu/MenuJoin.hpp"
#include "DrawableMenu/MenuRoot.hpp"
#include "DrawableMenu/MenuSettings.hpp"


RTypeMenuContext::RTypeMenuContext(std::shared_ptr<RType::EventManager> eventManager) : _eventManager(eventManager), _eventListener(eventManager) {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer);

    auto stratPos = vec2<float>(1500, 100);
    _pool->AddEntity("DeathStar", stratPos);

    stratPos = vec2<float>(1100, 450);
    _pool->AddEntity("Mars", stratPos);

    stratPos = vec2<float>(-100, -100);
    _pool->AddEntity("Ship", stratPos);

    _backgroundTexture.loadFromFile("sprites/spacebackground.jpg");
    _background.setTexture(_backgroundTexture);
    _font.loadFromFile("sprites/pdark.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(50);

    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuRoot()));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuCreate()));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuJoin()));
    _menu.push_back(std::unique_ptr<ADrawableMenu>(new MenuSettings()));

    _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        if (message->getEventType() == USER_UP || message->getEventType() == USER_DOWN || message->getEventType() == USER_LEFT || message->getEventType() == USER_RIGHT) {
            for (auto &&elem : _menu) {
                SFMLManager::soundManager->PlaySound("sprites/changeMenu.ogg");
                elem->moveSelection(message->getEventType());
            }
        } else if (message->getEventType() == USER_ENTER) {
            SFMLManager::soundManager->PlaySound("sprites/menuValidate.ogg");
            ADrawableMenu::moveIn(_menu, _eventManager);
        }
    });
}

void RTypeMenuContext::DrawMenu(sf::RenderTexture &context) {
    for (auto &&elem : _menu) {
        elem->Draw(context, _text);
    }
}

void RTypeMenuContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.create(1280, 720);
    context.clear(sf::Color::Black);
    context.draw(_background);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    DrawMenu(context);
    context.display();
}