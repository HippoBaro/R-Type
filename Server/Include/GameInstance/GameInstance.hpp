//
// Created by hippolyteb on 12/1/16.
//

#ifndef R_TYPE_GAMEINSTANCE_HPP
#define R_TYPE_GAMEINSTANCE_HPP

#include <EntityPool/EntityPool.hpp>
#include <EventDispatcher/EventManager.hpp>

class GameInstance {
private:
    uint16_t _id;
    std::unique_ptr<EntityPool> _pool = nullptr;
    RType::EventManager _eventManager = RType::EventManager();

public:
    GameInstance(uint16_t id);
};


#endif //R_TYPE_GAMEINSTANCE_HPP
