//
// Created by hippolyteb on 12/1/16.
//

#include <fstream>
#include "GameInstance/GameInstanceManager.hpp"

void GameInstanceManager::CreateInstance(std::vector<PlayerRef> &) {

    std::ifstream infile;
    infile.open("medias/partitions/testPartition.partition");

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    //auto timestamp = std::chrono::time_point<std::chrono::steady_clock>() + std::chrono::milliseconds(time_point);

    _instances.push_back(std::unique_ptr<GameInstance>(new GameInstance(10, _eventManager, data, std::chrono::steady_clock::now())));
}

GameInstanceManager::GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(
        eventManager) {}
