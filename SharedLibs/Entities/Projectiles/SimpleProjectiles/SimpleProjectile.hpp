//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_SIMPLEPROJECTILE_HPP
#define R_TYPE_SIMPLEPROJECTILE_HPP

#include <EntityPartition.hpp>

class SimpleProjectile {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);

public:
    SimpleProjectile(const std::initializer_list<void *> init);
    SimpleProjectile(Timer *, TimeRef const &, vec2<float> const &);
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
