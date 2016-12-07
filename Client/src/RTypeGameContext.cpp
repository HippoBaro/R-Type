//
// Created by pasteu_e on 27/11/16.
//

#include <Time/Timer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"

RTypeGameContext::RTypeGameContext() : _pool() {
    Timer *timer = new Timer(std::chrono::steady_clock::now());

    auto now = timer->getCurrent().GetRelative(std::chrono::seconds(5));
    auto stratPos = vec2<float>(0, 0);

    ManagedExternalInstance<Entity> monster(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableDummyMonster", { timer, _pool.getEventManager().get(), &now, &stratPos }, "createDrawable", "destroyDrawable"));

    _pool.AddEntity(monster);
}

void RTypeGameContext::Draw(sf::RenderTexture &context) {
    context.create(800, 600);
    context.clear(sf::Color::White);
    _pool.ProcessEntities();
    _pool.Draw(context);
    context.display();
}