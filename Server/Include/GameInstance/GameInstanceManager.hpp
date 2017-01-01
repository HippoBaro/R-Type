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
    int _lastInstanceId = -1;
    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;

public:
    GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager);


    int getLastInstanceId() const {
        return _lastInstanceId;
    }

public:
    void CreateInstance(const int id, const std::vector<std::shared_ptr<PlayerRef>> &, const std::string &partitionName);
};


#endif //R_TYPE_GAMEINSTANCEMANAGER_HPP
