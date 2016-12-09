//
// Created by pasteu_e on 27/11/16.
//

#include <Time/Timer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"
#include <fstream>

RTypeGameContext::RTypeGameContext(std::string const &partitionFile) : _pool() {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now() + std::chrono::seconds(50));
    _pool = std::make_shared<ClientEntityPool>(_timer);

    std::ifstream infile;
    infile.open(partitionFile);

    std::string data((std::istreambuf_iterator<char>(infile)),
                    std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    _pool->LoadPartition(data);
}

void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::Black);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}