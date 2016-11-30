//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENTBUILDER_HPP
#define R_TYPE_PARTITIONSEGMENTBUILDER_HPP

#include <memory>
#include "PartitionSegment.hpp"
#include "LinearCurve.hpp"
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

    PartitionSegmentBuilder(PartitionSegmentBuilder const &other){
        this->_curvingOption = other.getCurvingOption();
        this->_duration = other.getDuration();
        this->_endValue = other.getEndValue();
        this->_start = other.getStart();
        this->_startValue = other.getStartValue();
    }

    PartitionSegmentBuilder() {}

    PartitionSegmentBuilder &From(vec2<int> const &from){
        _startValue = from;
        return *this;
    }

    PartitionSegmentBuilder &To(vec2<int> const &to){
        _endValue = to;
        return *this;
    }

    PartitionSegmentBuilder &Begins(TimeRef const &begin){
        _start = begin;
        return *this;
    }

    PartitionSegmentBuilder &For(std::chrono::milliseconds const &duration){
        _duration = duration;
        return *this;
    }

    PartitionSegmentBuilder &WithCurving(ITweeningCurve *curve){
        _curvingOption = curve;
        return *this;
    }

    PartitionSegmentBuilder &Invert(){
        vec2<int> temp;
        temp = _startValue;
        _startValue = _endValue;
        _endValue = temp;
        return *this;
    }

    PartitionSegment Build(Timer *timer){
        if (_curvingOption == nullptr)
            _curvingOption = new LinearCurve();
        return PartitionSegment(Tween<vec2<int>>(timer, _startValue, _start, _endValue, TimeRef(_start.getMilliseconds() + _duration), _curvingOption));
    }

    ITweeningCurve *getCurvingOption() const{
        return _curvingOption;
    }

    const TimeRef &getStart() const{
        return _start;
    }

    const std::chrono::milliseconds &getDuration() const{
        return _duration;
    }

    const vec2<int> &getStartValue() const {
        return _startValue;
    }

    const vec2<int> &getEndValue() const {
        return _endValue;
    }
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
