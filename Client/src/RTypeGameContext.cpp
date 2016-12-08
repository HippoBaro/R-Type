//
// Created by pasteu_e on 27/11/16.
//

#include <Time/Timer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"

RTypeGameContext::RTypeGameContext() : _pool() {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer);
    _pool->LoadPartition("");
    //auto stratPos = vec2<float>(0, 0);

    //_pool->AddEntity("DummyMonster", stratPos);
}

void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::White);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}