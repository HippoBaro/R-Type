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
    std::vector<GameInstance> _instances;

public:
    void CreateInstance(std::vector<PlayerRef> &players);
};


#endif //R_TYPE_GAMEINSTANCEMANAGER_HPP
