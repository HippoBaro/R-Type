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
#include <Serializer/ISerializable.hpp>

class Entity : public RType::ISerializable {
protected:
    uint16_t _id;
    std::shared_ptr<Timer> _timer;
    std::shared_ptr<RType::EventManager> _eventManager;

    std::vector<Trait> _traits = std::vector<Trait>();
public:
    virtual ~Entity() { }

    Entity(uint16_t _id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventMgr) : _id(_id), _timer(timer), _eventManager(eventMgr) {}

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

    virtual void Serialize(RType::Packer &packer){
        std::cout << "Packing Entity base" << std::endl;
        packer.Pack(_id);
        packer.Pack(_traits);
    };
};

#endif //R_TYPE_IENTITY_HPP
