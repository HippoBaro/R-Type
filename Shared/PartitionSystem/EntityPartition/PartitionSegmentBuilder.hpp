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

    vec2d _startValue = vec2d();
    vec2d _endValue = vec2d();

public:

    PartitionSegmentBuilder(PartitionSegmentBuilder const &other);

    PartitionSegmentBuilder();

    PartitionSegmentBuilder &From(vec2d const &);
    PartitionSegmentBuilder &To(vec2d const &);
    PartitionSegmentBuilder &Begins(TimeRef const &);
    PartitionSegmentBuilder &For(std::chrono::milliseconds const &);
    template <class Curve> PartitionSegmentBuilder &WithCurving();
    PartitionSegmentBuilder &Invert();
    PartitionSegment Build(Timer *);

    ITweeningCurve *getCurvingOption() const;

    const TimeRef &getStart() const;

    const std::chrono::milliseconds &getDuration() const;

    const vec2d &getStartValue() const;

    const vec2d &getEndValue() const;
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
