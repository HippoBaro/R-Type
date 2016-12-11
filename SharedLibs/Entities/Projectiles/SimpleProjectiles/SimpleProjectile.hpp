//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_SIMPLEPROJECTILE_HPP
#define R_TYPE_SIMPLEPROJECTILE_HPP

#include <PartitionSystem/EntityPartition.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>

class SimpleProjectile : public Entity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    virtual ~SimpleProjectile();

public:
    SimpleProjectile(const std::initializer_list<void *> init);
    SimpleProjectile(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
