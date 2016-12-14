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
    std::shared_ptr<Timer> _timer = nullptr;
    RType::EventManager _eventManager = RType::EventManager();

public:
    GameInstance(uint16_t id, std::string const &partition, std::chrono::steady_clock::time_point const&);
};


#endif //R_TYPE_GAMEINSTANCE_HPP
