//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include <RTypeMenuContext.hpp>
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(new RTypeGameContext()), _menuContext(new RTypeMenuContext()) {

}

void SFMLManager::Run() {
    std::cout << "Coucou je suis dans le SFMLManager" << std::endl;
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(10));
}