//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Timer.hpp>
#include <Base.h>
#include <Interfaces/Libs/IDrawable.hpp>
#include <Interfaces/Libs/DrawableEntity.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class Player : public Entity {
protected:
    Timer *_timer;
    EntityPartition _partition;

public:
    Player(Timer *timer);
};

#endif //R_TYPE_DUMMYMONSTER_HPP