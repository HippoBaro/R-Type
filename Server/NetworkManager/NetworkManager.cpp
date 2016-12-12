//
// Created by hippolyteb on 12/12/16.
//

#include "NetworkManager/NetworkManager.hpp"

void NetworkManager::Start() {
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&NetworkManager::Run, this)));
}

void NetworkManager::Run() {
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
}
