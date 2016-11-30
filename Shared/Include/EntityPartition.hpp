//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_ENTITYPARTITION_HPP
#define R_TYPE_ENTITYPARTITION_HPP

#include <algorithm>
#include <vector>
#include "PartitionSegmentBuilder.hpp"

class EntityPartition {
private:
    std::vector<PartitionSegment> _segments;

public:
    EntityPartition(Timer *timer) : _segments(std::vector<PartitionSegment>()) {};

public:
    EntityPartition &AddSegment(PartitionSegment const &segment){
        _segments.push_back(segment);
        return *this;
    }

    PartitionSegment GetCurrentSegment(TimeRef const &timeRef){
        auto ret = *std::find_if(_segments.begin(), _segments.end(), [timeRef](PartitionSegment &arg) {
            return arg.isPartOf(timeRef);
        });

        if (ret.isPartOf(timeRef))
            return ret;
        return _segments.back();
    }
};


#endif //R_TYPE_ENTITYPARTITION_HPP
