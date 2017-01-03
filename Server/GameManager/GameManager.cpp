//
// Created by hippolyteb on 12/12/16.
//

#include "GameManager/GameManager.hpp"

GameManager::GameManager() {}

void GameManager::Start() {
    _networkManager->Start();
    _lobbyManager = std::unique_ptr<LobbyManager>(new LobbyManager(_eventManager, _networkManager));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}
