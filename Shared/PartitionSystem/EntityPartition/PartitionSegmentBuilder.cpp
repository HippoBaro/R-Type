//
// Created by hippolyteb on 11/25/16.
//

#include <LinearCurve.hpp>
#include "PartitionSegmentBuilder.hpp"

PartitionSegmentBuilder &PartitionSegmentBuilder::From(vec2<int> const &from) {
    _startValue = from;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::To(vec2<int> const &to) {
    _endValue = to;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::Begins(TimeRef const &begin) {
    _start = begin;
    return *this;
}

PartitionSegment PartitionSegmentBuilder::Build(Timer *timer) {
    if (_curvingOption == nullptr)
        _curvingOption = new LinearCurve();
    return PartitionSegment(Tween<vec2<int>>(timer, _startValue, _start, _endValue, TimeRef(_start.getMilliseconds() + _duration), _curvingOption));
}

PartitionSegmentBuilder &PartitionSegmentBuilder::WithCurving(ITweeningCurve *curve) {
    _curvingOption = curve;
    return *this;
}

PartitionSegmentBuilder &PartitionSegmentBuilder::For(std::chrono::milliseconds const &duration) {
    _duration = duration;
    return *this;
}

ITweeningCurve *PartitionSegmentBuilder::getCurvingOption() const {
    return _curvingOption;
}

const TimeRef &PartitionSegmentBuilder::getStart() const {
    return _start;
}

const std::chrono::milliseconds &PartitionSegmentBuilder::getDuration() const {
    return _duration;
}

const vec2<int> &PartitionSegmentBuilder::getStartValue() const {
    return _startValue;
}

const vec2<int> &PartitionSegmentBuilder::getEndValue() const {
    return _endValue;
}

PartitionSegmentBuilder::PartitionSegmentBuilder(PartitionSegmentBuilder const &other) {
    this->_curvingOption = other.getCurvingOption();
    this->_duration = other.getDuration();
    this->_endValue = other.getEndValue();
    this->_start = other.getStart();
    this->_startValue = other.getStartValue();
}

PartitionSegmentBuilder::PartitionSegmentBuilder() {}

PartitionSegmentBuilder &PartitionSegmentBuilder::Invert() {
    vec2<int> temp;
    temp = _startValue;
    _startValue = _endValue;
    _endValue = temp;
    return *this;
}
