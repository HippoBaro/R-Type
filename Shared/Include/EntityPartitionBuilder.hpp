//
// Created by hippolyteb on 11/26/16.
//

#ifndef R_TYPE_ENTITYPARTITIONBUILDER_HPP
#define R_TYPE_ENTITYPARTITIONBUILDER_HPP

#include "PartitionSegmentBuilder.hpp"
#include "EntityPartition.hpp"

class EntityPartitionBuilder {
private:
    std::vector<PartitionSegmentBuilder> _segments;
    Timer *_timer;
    vec2<int> _initialPosition;

public:
    EntityPartitionBuilder(Timer *timer, vec2<int> const &initialPos) : _segments(), _timer(timer), _initialPosition(initialPos) {}

public:
    EntityPartitionBuilder &AddSegment(PartitionSegmentBuilder &segment){
        if (_segments.size() == 0) {// if this is the very first segment
            segment.From(_initialPosition);
            auto translationvalue = segment.getTranslationValue();
            segment.To(_initialPosition + translationvalue);
        }
        else {
            segment.From(_segments.back().getEndValue());
            segment.Begins(TimeRef(_segments.back().getStart().getMilliseconds() + _segments.back().getDuration()));
            auto translationvalue = segment.getTranslationValue();
            auto lastEnd = segment.getStartValue();
            segment.To(lastEnd + translationvalue);
        }
        _segments.push_back(segment);
        return *this;
    }

    EntityPartitionBuilder &Loop(int const count) {
        for (int i = 0; i < count - 1; ++i) {
            auto last = PartitionSegmentBuilder(_segments.back());
            last.Invert();
            AddSegment(last);
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
