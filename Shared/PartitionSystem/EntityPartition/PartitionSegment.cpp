//
// Created by hippolyteb on 11/25/16.
//

#include "PartitionSegment.hpp"

const Tween<vec2d> &PartitionSegment::getLocationVector() const {
    return _locationVector;
}

PartitionSegment::PartitionSegment(const Tween<vec2d> &locationVector) : _locationVector(
        locationVector) {}

PartitionSegment::PartitionSegment() : _locationVector() {}
