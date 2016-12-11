//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_ENTITYPARTITION_HPP
#define R_TYPE_ENTITYPARTITION_HPP

#include <vector>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

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

    PartitionSegment *GetCurrentSegment(TimeRef const &timeRef){
		for(auto &i : _segments)
			if (i.isPartOf(timeRef))
				return &i;

        if (_segments.front().getStart() > timeRef)
            return &_segments.front();

        return &_segments.back();
    }

    bool isPartitionPlayed(TimeRef const &ref){
        return _segments.back().getEnd() <= ref;
    }

    TimeRef getStart() {
        return _segments.front().getStart();
    }

    TimeRef getEnd() {
        return _segments.back().getEnd();
    }

    bool ShouldFire(TimeRef const &timeRef) {
        if (_segments.size() == 0)
            return false;
        auto start = getStart();
        auto end = getEnd();
        if (timeRef < start || timeRef > end)
            return false;
        auto segment = GetCurrentSegment(timeRef);
        return segment->ShouldFireNow(timeRef);
    }
};


#endif //R_TYPE_ENTITYPARTITION_HPP
