//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_ENTITYPARTITION_HPP
#define R_TYPE_ENTITYPARTITION_HPP

#include <vector>
#include "PartitionSegmentBuilder.hpp"

class EntityPartition {
private:
    Timer *_timer;
    std::vector<PartitionSegment> _segments;

public:
    EntityPartition(Timer *);

public:
    EntityPartition &AddSegment(PartitionSegment const &segment);
    PartitionSegment GetCurrentSegment(TimeRef const &timeRef);
};


#endif //R_TYPE_ENTITYPARTITION_HPP
