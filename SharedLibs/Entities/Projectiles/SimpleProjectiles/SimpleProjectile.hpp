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
    EntityPartition _partition = EntityPartition(_timer);

public:
    virtual ~SimpleProjectile();

public:
    SimpleProjectile(const std::initializer_list<void *> init);
    SimpleProjectile(uint16_t, Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
