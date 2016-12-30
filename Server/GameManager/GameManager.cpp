//
// Created by hippolyteb on 12/12/16.
//

#include "GameManager/GameManager.hpp"
#include <chrono>
#include <LobbyManager/LobbyManager.hpp>

void GameManager::Start() {
//    _lobbyManager = std::unique_ptr<std::thread>(new std::thread(std::bind(&LobbyManager::Start, this)));
//    std::cout << "Starting "
    _networkManager.Start();
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}