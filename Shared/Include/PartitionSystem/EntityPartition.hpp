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

    PartitionSegment GetCurrentSegment(TimeRef const &timeRef){
		for(auto i : _segments)
			if (i.isPartOf(timeRef))
				return i;

        if (_segments.front().getStart() > timeRef)
            return _segments.front();

        return _segments.back();
    }
};


#endif //R_TYPE_ENTITYPARTITION_HPP
