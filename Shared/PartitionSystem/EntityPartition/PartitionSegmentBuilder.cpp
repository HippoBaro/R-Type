//
// Created by hippolyteb on 11/25/16.
//

#include <LinearCurve.hpp>
#include "PartitionSegmentBuilder.hpp"

PartitionSegmentBuilder &PartitionSegmentBuilder::From(vec2d const &from) {
    _startValue = from;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::To(vec2d const &to) {
    _endValue = to;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::Begins(TimeRef const &begin) {
    _start = begin;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::Ends(TimeRef const &end) {
    _end = TimeRef(end);
    return *this;
}

PartitionSegment PartitionSegmentBuilder::Build(Timer *timer) {
    if (_curvingOption == nullptr)
        _curvingOption = new LinearCurve();
    return PartitionSegment(Tween<vec2d>(timer, _startValue, _start, _endValue, _end, _curvingOption));
}

template<class Curve>
PartitionSegmentBuilder &PartitionSegmentBuilder::WithCurving() {
    _curvingOption = new Curve();
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::BeginsAfterPrevious() {
    return *this;
}
