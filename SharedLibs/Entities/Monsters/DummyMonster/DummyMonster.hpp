//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP


#include "../../../../Shared/PartitionSystem/EntityPartition/EntityPartition.hpp"
#include "../../../../Shared/Libs/Interfaces/IEntity.hpp"
#include "../../../../Shared/Include/Timer.hpp"
#include "../../../Base.h"
#include "../../../../Shared/PartitionSystem/EntityPartition/PartitionSegmentBuilder.hpp"

class DummyMonster : public IEntity {
private:
    std::shared_ptr<Timer> _timer;
    EntityPartition _partition;

public:
    DummyMonster(std::shared_ptr<Timer> &timer);
};


#endif //R_TYPE_DUMMYMONSTER_HPP
