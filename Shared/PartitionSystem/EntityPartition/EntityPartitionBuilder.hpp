//
// Created by hippolyteb on 11/26/16.
//

#ifndef R_TYPE_ENTITYPARTITIONBUILDER_HPP
#define R_TYPE_ENTITYPARTITIONBUILDER_HPP


#include "PartitionSegmentBuilder.hpp"
#include "EntityPartition.hpp"

class EntityPartitionBuilder {
private:
    std::vector<PartitionSegmentBuilder> _segments;
    Timer *_timer;

public:
    EntityPartitionBuilder(Timer *);

public:
    EntityPartitionBuilder &AddSegment(PartitionSegmentBuilder &segment);
    EntityPartitionBuilder &ContinueWith(PartitionSegmentBuilder &segment);
    EntityPartitionBuilder &Loop(int const count);
    EntityPartition Build();
};


#endif //R_TYPE_ENTITYPARTITIONBUILDER_HPP
