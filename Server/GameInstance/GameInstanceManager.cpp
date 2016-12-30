//
// Created by hippolyteb on 12/1/16.
//

#include <fstream>
#include <Messages/StartNewGameMessage.hpp>
#include "GameInstance/GameInstanceManager.hpp"

void GameInstanceManager::CreateInstance(std::vector<PlayerRef> &) {

    std::ifstream infile;
    infile.open("medias/partitions/testPartition.partition");

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    _instances.push_back(std::unique_ptr<GameInstance>(new GameInstance(10, _eventManager, data, std::chrono::steady_clock::now())));
}

GameInstanceManager::GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager) :
        _eventManager(eventManager),
        _eventListener(eventManager)
{
    _eventListener.Subscribe<void, StartNewGameMessage>(RType::Event::START_NEW_GAME, [](void *, StartNewGameMessage *message) {
       std::cout << "TOTO"<< std::endl;
    });
}
