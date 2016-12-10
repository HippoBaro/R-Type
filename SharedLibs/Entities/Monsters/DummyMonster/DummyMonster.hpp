//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class DummyMonster : public Entity {
protected:
    EntityPartition _partition = EntityPartition(_timer);

public:
    DummyMonster(const std::initializer_list<void *> init);
    DummyMonster(uint16_t, Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};

#endif //R_TYPE_DUMMYMONSTER_HPP