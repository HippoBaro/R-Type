//
// Created by pasteu_e on 27/11/16.
//

#include <Timer.hpp>
#include <ManagedExternalInstance.hpp>
#include <ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"

RTypeGameContext::RTypeGameContext() : _pool() {
    Timer *timer = new Timer(std::chrono::system_clock::now());

    auto now = timer->getCurrent().GetRelative(std::chrono::seconds(5));
    auto stratPos = vec2<float>(0, 0);

    ManagedExternalInstance<Entity> monster(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableDummyMonster", { timer, &now, &stratPos }, "createDrawable", "destroyDrawable"));

    _pool.AddEntity(monster);
}

void RTypeGameContext::Draw(sf::RenderTexture &context) {
    context.create(800, 600);
    context.clear(sf::Color::White);
    _pool.Draw(context);
    context.display();
}