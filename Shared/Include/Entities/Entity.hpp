//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_IENTITY_HPP
#define R_TYPE_IENTITY_HPP

#include <algorithm>
#include "Trait.hpp"
#include <vector>

class Entity {
protected:
    std::vector<Trait> _traits = std::vector<Trait>();
public:
    virtual ~Entity() { }

    virtual bool ImplementTrait(Trait &trait) {
        for(auto &x : _traits)
            if (x == trait) return true;
        return false;
    }

    virtual void RegisterTrait(Trait trait) {
        _traits.push_back(trait);
    }

    virtual void Cycle() = 0;
};

#endif //R_TYPE_IENTITY_HPP
