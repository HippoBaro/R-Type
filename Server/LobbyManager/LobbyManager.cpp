//
// Created by pasteu_e on 17/12/16.
//

#include "LobbyManager/LobbyManager.hpp"

void LobbyManager::Start() {
    _networkManager.Start();
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
}