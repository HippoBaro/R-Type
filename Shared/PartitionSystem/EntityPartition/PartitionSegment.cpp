//
// Created by hippolyteb on 11/25/16.
//

#include "PartitionSegment.hpp"

Tween<vec2<unsigned int>> PartitionSegment::getLocationVector() const {
    return _locationVector;
}

PartitionSegment::PartitionSegment(const Tween<vec2<unsigned int>> &locationVector) : _locationVector(
        locationVector) {}

PartitionSegment::PartitionSegment() : _locationVector() {}

bool PartitionSegment::isPartOf(TimeRef const &timeRef) {
    return this->_locationVector.isPartOf(timeRef);
}
