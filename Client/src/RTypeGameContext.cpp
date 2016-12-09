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
    _pool->LoadPartition("{\n"
                         "\t\"partitionName\":\"TestPartition\",\n"
                         "\t\"backgroundTheme\":\"test.ogg\",\n"
                         "\t\"backgroundEntity\": \n"
                         "\t\t{\n"
                         "\t\t\t\"entityName\":\"testEntity\",\n"
                         "\t\t\t\"startPosition\": {\n"
                         "\t\t\t\t\"x\":0,\n"
                         "\t\t\t\t\"y\":0\n"
                         "\t\t}\n"
                         "\t},\n"
                         "\t\"entities\":[\n"
                         "\t\t{\n"
                         "\t\t\t\"entityName\":\"DummyMonster\",\n"
                         "\t\t\t\"startPosition\": {\n"
                         "\t\t\t\t\"x\":0,\n"
                         "\t\t\t\t\"y\":0\n"
                         "\t\t\t},\n"
                         "\t\t\t\"startTime\":1000\n"
                         "\t\t}\n"
                         "\t]\n"
                         "}");
}

void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::Black);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}