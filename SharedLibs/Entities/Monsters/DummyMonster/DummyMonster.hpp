//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include "EntityPartition.hpp"
#include <IEntity.hpp>
#include <Timer.hpp>
#include <Base.h>
#include "PartitionSegmentBuilder.hpp"

class DummyMonster : public IEntity {
private:
    Timer *_timer;
    EntityPartition _partition;

public:
    DummyMonster(Timer *timer);
};


#endif //R_TYPE_DUMMYMONSTER_HPP
