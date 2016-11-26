//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_ENTITYPARTITION_HPP
#define R_TYPE_ENTITYPARTITION_HPP

#include <vector>
#include "IEntity.hpp"
#include "PartitionSegment.hpp"

class EntityPartition : public IEntity {
private:
    std::vector<PartitionSegment> _segments;

public:
    EntityPartition();

public:
    EntityPartition &AddSegment(PartitionSegment const &segment);
    EntityPartition &Repeat(int const count);
    PartitionSegment GetCurrentSegment(TimeRef const &timeRef);
};


#endif //R_TYPE_ENTITYPARTITION_HPP
