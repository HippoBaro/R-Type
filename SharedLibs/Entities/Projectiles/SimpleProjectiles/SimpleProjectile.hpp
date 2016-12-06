//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_SIMPLEPROJECTILE_HPP
#define R_TYPE_SIMPLEPROJECTILE_HPP

#include <PartitionSystem/EntityPartition.hpp>
#include <EventDispatcher/EventManager.hpp>

class SimpleProjectile {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    SimpleProjectile(const std::initializer_list<void *> init);
    SimpleProjectile(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
