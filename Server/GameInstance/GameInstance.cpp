//
// Created by hippolyteb on 12/1/16.
//

#include "GameInstance/GameInstance.hpp"

GameInstance::GameInstance(uint16_t id, const std::shared_ptr<RType::EventManager> &globalEventManager,
                           std::string const &partition,
                           std::chrono::steady_clock::time_point const &origin) : _id(id),
                                                                                  _globalEventManager(globalEventManager) {
    _timer = std::make_shared<Timer>(origin);
    _pool = std::unique_ptr<ServerEntityPool>(new ServerEntityPool(_timer, _eventManager));
    _pool->LoadPartition(partition);
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&GameInstance::Start, this)));
}

void GameInstance::Start() {
    auto t = std::chrono::steady_clock::now();

    while (true) //todo : loop must break when game is over
    {
        _pool->ProcessEntities();
        _pool->BroadcastEntities(_globalEventManager);
        t += std::chrono::milliseconds(1000); //We'll send entities 60 times per seconds
        std::this_thread::sleep_until(t);
    }
}
