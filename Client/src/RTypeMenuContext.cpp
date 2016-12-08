//
// Created by pasteu_e on 27/11/16.
//

#include <vec2.hpp>
#include <Time/Timer.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeMenuContext.hpp"

RTypeMenuContext::RTypeMenuContext() : _backgroundTexture(), _background(), _font(), _text(), _menuRoot() {
    Timer *timer = new Timer(std::chrono::steady_clock::now());
    auto now = timer->getCurrent();
    auto stratPos = vec2<float>(1500, 100);
    ManagedExternalInstance<Entity> depth_star(
            ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableDeathStar", {timer, nullptr, &now, &stratPos}, "createDrawable", "destroyDrawable"));
    _pool.AddEntity(depth_star);

    now = timer->getCurrent();
    stratPos = vec2<float>(1500, 450);
    ManagedExternalInstance<Entity> mars(
            ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableMars", {timer, nullptr, &now, &stratPos}, "createDrawable", "destroyDrawable"));
    _pool.AddEntity(mars);

    _backgroundTexture.loadFromFile("sprites/spacebackground.png");
    _background.setTexture(_backgroundTexture);
    _font.loadFromFile("sprites/pdark.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(50);
    _menuRoot["Create Room"] = true;
    _menuRoot["Join Room"] = false;
    _menuRoot["Settings"] = false;
    _menuRoot["Quit"] = false;
}

void RTypeMenuContext::DrawMenu(sf::RenderTexture &context, std::map<std::string, bool> &menu) {
    int i = 1;
    long y = (context.getSize().y / 2) - (((50 * menu.size()) + (50 * (menu.size() - 2))) / 2);
    for (auto &elem : menu) {
        if (elem.second)
            _text.setFillColor(sf::Color::Red);
        else
            _text.setFillColor(sf::Color::White);
        _text.setString(elem.first);
        _text.setPosition(150, y + (50 * i));
        context.draw(_text);
        i++;
    }
}

void RTypeMenuContext::Draw(sf::RenderTexture &, TextureBag &) {
    context.create(1280, 720);
    context.clear(sf::Color::Black);
    context.draw(_background);
    _pool.Draw(context);
    DrawMenu(context, _menuRoot);
    context.display();
}
