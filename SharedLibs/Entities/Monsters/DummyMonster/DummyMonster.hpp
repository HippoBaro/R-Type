//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Timer.hpp>
#include <Base.h>
#include <Interfaces/Libs/Entity.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class DummyMonster : public Entity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);

public:
    DummyMonster(const std::initializer_list<void *> init);
    DummyMonster(Timer *, TimeRef const &, vec2<float> const &);
};

#endif //R_TYPE_DUMMYMONSTER_HPP