//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_IENTITY_HPP
#define R_TYPE_IENTITY_HPP

#include <algorithm>
#include "Trait.hpp"
#include <vector>
#include <Time/Timer.hpp>
#include <EventDispatcher/EventManager.hpp>

class Entity {
protected:
    uint16_t _id;
    Timer *_timer = nullptr;
    RType::EventManager *_eventManager;

    std::vector<Trait> _traits = std::vector<Trait>();
public:
    virtual ~Entity() { }

    Entity(uint16_t _id, Timer *timer, RType::EventManager *eventMgr) : _id(_id), _timer(timer), _eventManager(eventMgr) {}

    virtual bool ImplementTrait(Trait trait) {
        for(auto x : _traits)
            if (x == trait)
                return true;
        return false;
    }

    virtual void RegisterTrait(Trait trait) {
        _traits.push_back(trait);
    }

    virtual void Destroy(){
        RegisterTrait(Garbage);
    }

    uint16_t getId() const {
        return _id;
    }

    virtual void Cycle() = 0;
};

#endif //R_TYPE_IENTITY_HPP
