//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include "EntityPartition.hpp"
#include <Timer.hpp>
#include <Base.h>
#include <IDrawable.hpp>
#include <DrawableEntity.hpp>
#include "PartitionSegmentBuilder.hpp"

class DummyMonster : public Entity {
protected:
    Timer *_timer;
    EntityPartition _partition;

public:
    DummyMonster(Timer *timer);
};

#endif //R_TYPE_DUMMYMONSTER_HPP