//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENTBUILDER_HPP
#define R_TYPE_PARTITIONSEGMENTBUILDER_HPP

#include <memory>
#include "PartitionSegment.hpp"
#include "PartitionSystem/Tween/Curve/LinearCurve.hpp"
#include <PartitionSystem/Tween/Curve/ITweeningCurve.hpp>
#include <vec2.hpp>

class PartitionSegmentBuilder {
private:
    ITweeningCurve *_curvingOption = nullptr;

    TimeRef _start = TimeRef();
    std::chrono::milliseconds _duration = std::chrono::milliseconds();

    vec2<float> _startValue = vec2<float>();
    vec2<float> _endValue = vec2<float>();
    vec2<float> _translationValue = vec2<float>();
    float _fireRate = 0;
    std::string _projectileType = "";

public:

    PartitionSegmentBuilder(PartitionSegmentBuilder const &other){
        this->_curvingOption = other.getCurvingOption();
        this->_duration = other.getDuration();
        this->_endValue = other.getEndValue();
        this->_start = other.getStart();
        this->_startValue = other.getStartValue();
        this->_projectileType = other.getProjectileType();
        this->_translationValue = other.getTranslationValue();
        this->_fireRate = other.getFireRate();
    }

    PartitionSegmentBuilder() {}

    PartitionSegmentBuilder &From(vec2<float> const &from){
        _startValue = from;
        return *this;
    }

    PartitionSegmentBuilder &Translate(vec2<float> const &delta){
        _translationValue = delta;
        return *this;
    }

    PartitionSegmentBuilder &To(vec2<float> const &to){
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

    PartitionSegmentBuilder &Fire(std::string const &projectileType, float ratePerSecond) {
        _fireRate = ratePerSecond;
        _projectileType = projectileType;
        return *this;
    }

    PartitionSegmentBuilder &Invert(){
        vec2<float> temp;
        temp = _startValue;
        _startValue = _endValue;
        _translationValue = temp - _endValue;
        return *this;
    }

    PartitionSegment Build(std::shared_ptr<Timer> timer){
        if (_curvingOption == nullptr)
            _curvingOption = new LinearCurve();
        return PartitionSegment(Tween<vec2<float>>(timer, _startValue, _start, _endValue,
                                                   TimeRef(_start.getMilliseconds() + _duration),
                                                   _curvingOption),
                                _fireRate, _projectileType);
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

    const vec2<float> &getStartValue() const {
        return _startValue;
    }

    const vec2<float> &getEndValue() const {
        return _endValue;
    }

    const vec2<float> &getTranslationValue() const {
        return _translationValue;
    }

    float getFireRate() const {
        return _fireRate;
    }

    const std::string &getProjectileType() const {
        return _projectileType;
    }
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
