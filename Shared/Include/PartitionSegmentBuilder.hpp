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

    vec2<unsigned int> _startValue = vec2<unsigned int>();
    vec2<unsigned int> _endValue = vec2<unsigned int>();

public:

    PartitionSegmentBuilder(PartitionSegmentBuilder const &other);

    PartitionSegmentBuilder();

    PartitionSegmentBuilder &From(vec2<unsigned int> const &);
    PartitionSegmentBuilder &To(vec2<unsigned int> const &);
    PartitionSegmentBuilder &Begins(TimeRef const &);
    PartitionSegmentBuilder &For(std::chrono::milliseconds const &);
    template <class Curve> PartitionSegmentBuilder &WithCurving();
    PartitionSegmentBuilder &Invert();
    PartitionSegment Build(Timer *);

    ITweeningCurve *getCurvingOption() const;

    const TimeRef &getStart() const;

    const std::chrono::milliseconds &getDuration() const;

    const vec2<unsigned int> &getStartValue() const;

    const vec2<unsigned int> &getEndValue() const;
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
