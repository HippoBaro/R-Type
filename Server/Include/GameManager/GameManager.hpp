//
// Created by hippolyteb on 12/12/16.
//

#ifndef R_TYPE_GAMEMANAGER_HPP
#define R_TYPE_GAMEMANAGER_HPP


#include <thread>
#include <vector>
#include <GameInstance/GameInstance.hpp>
#include <NetworkManager/NetworkManager.hpp>

class GameManager {
private:
    std::vector<GameInstance> _instances = std::vector<GameInstance>();
    NetworkManager _networkManager = NetworkManager();

public:
    void Start();

};


#endif //R_TYPE_GAMEMANAGER_HPP
