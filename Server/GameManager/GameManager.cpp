//
// Created by hippolyteb on 12/12/16.
//

#include "GameManager/GameManager.hpp"
#include <chrono>

void GameManager::Start() {
    _networkManager.Start();
    auto temp = std::vector<PlayerRef>();
    _gameInstanceManager.CreateInstance(temp);

    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}