//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENTBUILDER_HPP
#define R_TYPE_PARTITIONSEGMENTBUILDER_HPP

#include <memory>
#include "PartitionSegment.hpp"
#include <ITweeningCurve.hpp>
#include <vec2.hpp>

class PartitionSegmentBuilder {
private:
    ITweeningCurve *_curvingOption = nullptr;

    TimeRef _start = TimeRef();
    std::chrono::milliseconds _duration =std::chrono::milliseconds();

    vec2<int> _startValue = vec2<int>();
    vec2<int> _endValue = vec2<int>();

public:

    PartitionSegmentBuilder(PartitionSegmentBuilder const &other);

    PartitionSegmentBuilder();

    PartitionSegmentBuilder &From(vec2<int> const &);
    PartitionSegmentBuilder &To(vec2<int> const &);
    PartitionSegmentBuilder &Begins(TimeRef const &);
    PartitionSegmentBuilder &For(std::chrono::milliseconds const &);
    PartitionSegmentBuilder &WithCurving(ITweeningCurve *curve);
    PartitionSegmentBuilder &Invert();
    PartitionSegment Build(Timer *);

    ITweeningCurve *getCurvingOption() const;

    const TimeRef &getStart() const;

    const std::chrono::milliseconds &getDuration() const;

    const vec2<int> &getStartValue() const;

    const vec2<int> &getEndValue() const;
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
