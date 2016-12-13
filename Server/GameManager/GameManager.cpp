//
// Created by hippolyteb on 12/12/16.
//

#include "GameManager/GameManager.hpp"

void GameManager::Start() {
    _networkManager.Start();
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
}