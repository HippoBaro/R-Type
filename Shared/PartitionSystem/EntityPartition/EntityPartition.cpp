//
// Created by hippolyteb on 11/25/16.
//

#include "EntityPartition.hpp"

EntityPartition::EntityPartition() : _segments(std::vector<PartitionSegment>()) {}

EntityPartition &EntityPartition::AddSegment(PartitionSegment const &segment) {
    _segments.push_back(segment);
    return *this;
}

EntityPartition &EntityPartition::Repeat(int const count) {
    for (int i = 0; i < count - 1; ++i)
        AddSegment(_segments.back());
    return *this;
}
