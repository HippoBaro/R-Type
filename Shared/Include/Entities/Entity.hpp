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
#include <vec2.hpp>
#include <random>

class Entity : public RType::ISerializable {
protected:
    uint16_t _id;
    std::shared_ptr<Timer> _timer;
    std::shared_ptr<RType::EventManager> _eventManager;
    std::default_random_engine _ramdomGeneratorSeed;
    std::mt19937 _ramdomGenerator;
    uint8_t _cycleSinceLastSynch = 0;

    std::set<Trait> _traits = std::set<Trait>();
public:
    virtual ~Entity() { }

    Entity(uint16_t _id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventMgr) : _id(_id), _timer(timer), _eventManager(eventMgr), _ramdomGeneratorSeed(_id), _ramdomGenerator(std::mt19937(_ramdomGeneratorSeed())) {}

    virtual bool ImplementTrait(Trait trait) {
        for(auto x : _traits)
            if (x == trait)
                return true;
        return false;
    }

    virtual void RegisterTrait(Trait trait) {
        _traits.insert(trait);
    }

    virtual void Destroy(){
        RegisterTrait(Garbage);
    }

    uint16_t getId() const {
        return _id;
    }

    virtual uint16_t getTypeId() const = 0;

    virtual void Cycle() = 0;

    virtual vec2<float> GetRenderRect() = 0;
    virtual vec2<float> GetPosition() = 0;

    virtual void Serialize(RType::Packer &packer) {
        packer.Pack(_id);
        packer.Pack(_traits, true);
    };

    uint8_t getCyclesSinceLastSynch() const {
        return _cycleSinceLastSynch;
    }

    void DidSynch() {
        _cycleSinceLastSynch = 1;
    }

    void DidCycleNoSynch() {
        _cycleSinceLastSynch++;
    }
};

#endif //R_TYPE_IENTITY_HPP
