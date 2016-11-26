//
// Created by hippolyteb on 11/25/16.
//

#include <algorithm>
#include "EntityPartition.hpp"

EntityPartition::EntityPartition(Timer *timer) : _timer(timer), _segments(std::vector<PartitionSegment>()) {}

EntityPartition &EntityPartition::AddSegment(PartitionSegmentBuilder &segment) {
    _segments.push_back(segment.Build(_timer));
    return *this;
}

EntityPartition &EntityPartition::AddSegment(PartitionSegment const &segment) {
    _segments.push_back(segment);
    return *this;
}

EntityPartition &EntityPartition::Repeat(int const count) {
    for (int i = 0; i < count - 1; ++i)
        AddSegment(_segments.back());
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

EntityPartition &EntityPartition::ContinueWith(PartitionSegmentBuilder &segment) {
    _segments.push_back(segment.Begins(_segments.back().getLocationVector().getEnd()).Build(_timer));
    return *this;
}
