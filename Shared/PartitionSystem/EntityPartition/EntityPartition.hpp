//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_ENTITYPARTITION_HPP
#define R_TYPE_ENTITYPARTITION_HPP

#include <vector>
#include "IEntity.hpp"
#include "PartitionSegmentBuilder.hpp"

class EntityPartition : public IEntity {
private:
    Timer *_timer;
    std::vector<PartitionSegment> _segments;

public:
    EntityPartition(Timer *);

public:
    EntityPartition &AddSegment(PartitionSegmentBuilder &segment);
    EntityPartition &AddSegment(PartitionSegment const &segment);
    EntityPartition &ContinueWith(PartitionSegmentBuilder &segment);
    EntityPartition &Repeat(int const count);
    PartitionSegment GetCurrentSegment(TimeRef const &timeRef);
};


#endif //R_TYPE_ENTITYPARTITION_HPP
