//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_SIMPLEPROJECTILE_HPP
#define R_TYPE_SIMPLEPROJECTILE_HPP

#include <EntityPartition.hpp>

class SimpleProjectile {
protected:
    Timer *_timer;
    EntityPartition _partition;

public:
    SimpleProjectile(Timer *timer);
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
