//
// Created by hippolyteb on 11/25/16.
//

#include <algorithm>
#include "EntityPartition.hpp"

EntityPartition::EntityPartition(Timer *timer) : _timer(timer), _segments(std::vector<PartitionSegment>()) {}

EntityPartition &EntityPartition::AddSegment(PartitionSegment const &segment) {
    _segments.push_back(segment);
    return *this;
}

PartitionSegment EntityPartition::GetCurrentSegment(TimeRef const &timeRef) {
    auto ret = *std::find_if(_segments.begin(), _segments.end(), [timeRef](PartitionSegment &arg) {
        return arg.isPartOf(timeRef);
    });

    if (ret.isPartOf(timeRef))
        return ret;
    return _segments.back();
}
