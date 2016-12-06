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
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    DummyMonster(const std::initializer_list<void *> init);
    DummyMonster(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);
};

#endif //R_TYPE_DUMMYMONSTER_HPP