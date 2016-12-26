//
// Created by hippolyteb on 12/12/16.
//

#ifndef R_TYPE_GAMEMANAGER_HPP
#define R_TYPE_GAMEMANAGER_HPP


#include <thread>
#include <vector>
#include <NetworkManager/NetworkManager.hpp>
#include <GameInstance/GameInstanceManager.hpp>

class GameManager {
private:
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    NetworkManager _networkManager = NetworkManager(_eventManager);
    GameInstanceManager _gameInstanceManager = GameInstanceManager(_eventManager);

public:
    void Start();

};


#endif //R_TYPE_GAMEMANAGER_HPP
