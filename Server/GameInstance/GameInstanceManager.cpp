//
// Created by hippolyteb on 12/1/16.
//

#include <fstream>
#include <Messages/StartNewGameMessage.hpp>
#include "GameInstance/GameInstanceManager.hpp"

void GameInstanceManager::CreateInstance(std::vector<std::shared_ptr<PlayerRef>> players, const std::string &partitionName) {
    std::ifstream infile;
    infile.open(partitionName);

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    // TODO: generate ID based on previous IDs
    _instances.push_back(std::unique_ptr<GameInstance>(new GameInstance(10, _eventManager, data, std::chrono::steady_clock::now())));
}

GameInstanceManager::GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager) :
        _eventManager(eventManager),
        _eventListener(eventManager)
{
    _eventListener.Subscribe<void, StartNewGameMessage>(RType::Event::START_NEW_GAME, [this](void *, StartNewGameMessage *message) {
        CreateInstance(message->getPlayerRefs(), "medias/partitions/" + message->getPartition() + ".partition");
    });
}

