//
// Created by hippolyteb on 11/26/16.
//

#ifndef R_TYPE_ENTITYPARTITIONBUILDER_HPP
#define R_TYPE_ENTITYPARTITIONBUILDER_HPP

#include "PartitionSystem/PartitionSegmentBuilder.hpp"
#include "EntityPartition.hpp"

class EntityPartitionBuilder {
private:
    std::vector<PartitionSegmentBuilder> _segments;
    Timer *_timer;

public:
    EntityPartitionBuilder(Timer *timer) : _segments(), _timer(timer) {}

public:
    EntityPartitionBuilder &AddSegment(PartitionSegmentBuilder &segment){
        _segments.push_back(segment);
        return *this;
    }

    EntityPartitionBuilder &ContinueWith(PartitionSegmentBuilder &segment){
        segment.Begins(TimeRef(_segments.back().getStart().getMilliseconds() + _segments.back().getDuration()));
        segment.From(vec2<int>(_segments.back().getEndValue()));
        _segments.push_back(segment);
        return *this;
    }

    EntityPartitionBuilder &Loop(int const count) {
        for (int i = 0; i < count - 1; ++i) {
            auto last = PartitionSegmentBuilder(_segments.back());
            last.Invert();
            ContinueWith(last);
        }
        return *this;
    }

    EntityPartition Build(){
        EntityPartition ret(_timer);
        for (auto& i : _segments)
            ret.AddSegment(i.Build(_timer));
        return ret;
    }
};


#endif //R_TYPE_ENTITYPARTITIONBUILDER_HPP
