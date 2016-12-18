//
// Created by hippolyteb on 12/1/16.
//

#ifndef R_TYPE_GAMEINSTANCEMANAGER_HPP
#define R_TYPE_GAMEINSTANCEMANAGER_HPP

#include <EventDispatcher/EventManager.hpp>
#include <EntityPool/EntityPool.hpp>
#include <Entities/PlayerRef.hpp>
#include "GameInstance.hpp"

class GameInstanceManager {
private:
    std::vector<std::unique_ptr<GameInstance>> _instances = std::vector<std::unique_ptr<GameInstance>>();
    std::shared_ptr<RType::EventManager> _eventManager;

public:
    GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager);

public:
    void CreateInstance(std::vector<PlayerRef> &players);
};


#endif //R_TYPE_GAMEINSTANCEMANAGER_HPP
