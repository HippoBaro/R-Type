//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_TWEEN_HPP
#define R_TYPE_TWEEN_HPP

#include <memory>
#include <math.h>
#include "PartitionSystem/Tween/Curve/ITweeningCurve.hpp"
#include "Time/Timer.hpp"

template <typename TweenInnerType>
class Tween : public RType::ISerializable {

private:
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<ITweeningCurve> _curvingOption;

    TweenInnerType _startValue;
    TweenInnerType _endValue;

    TimeRef _start;
    TimeRef _end;

    TweenInnerType _delta;
    TweenInnerType _maxValue;

public:
    template <class TweeningCurve>
    Tween(std::shared_ptr<Timer> timer, TweenInnerType const &startValue, TimeRef const &start,
          TweenInnerType const &endValue, TimeRef const &end) : _timer(timer), _curvingOption(nullptr),
                                                                _startValue(startValue), _endValue(endValue), _start(start), _end(end),
                                                                _delta(_endValue - _startValue), _maxValue(std::numeric_limits<TweenInnerType>::max()){
        static_assert(std::is_base_of<ITweeningCurve, TweeningCurve>::value, "TweeningCurve must be a descendant of ITweeningCurve");
        _curvingOption = std::shared_ptr<TweeningCurve>(new TweeningCurve());
    }

    Tween(std::shared_ptr<Timer> timer, TweenInnerType const &startValue, TimeRef const &start,
         TweenInnerType const &endValue, TimeRef const &end, std::shared_ptr<ITweeningCurve> curve) : _timer(timer),_curvingOption(curve),
                                                               _startValue(startValue), _endValue(endValue), _start(start), _end(end),
                                                               _delta(_endValue - _startValue), _maxValue(std::numeric_limits<TweenInnerType>::max()){ }

    Tween() : _timer(nullptr),_curvingOption(nullptr),
            _startValue(), _endValue(), _start(), _end(),
            _delta(), _maxValue() { }

    TweenInnerType GetTweened() {
        auto now = _timer->getCurrent();
        auto currentTimeAsDouble = ((double)(now.getMilliseconds().count() - _start.getMilliseconds().count()) /
                ((double)(_end.getMilliseconds().count() - _start.getMilliseconds().count())));
        if (currentTimeAsDouble < 0)
            return _startValue;
        if (currentTimeAsDouble >= 1)
            return _endValue;

        return _startValue + (TweenInnerType)(_delta * _curvingOption->Curve(currentTimeAsDouble));
    }

    bool isPartOf(TimeRef const &timeRef) {
        return timeRef <= _end && timeRef >= _start;
    }

    const std::shared_ptr<ITweeningCurve> getCurvingOption() const {
        return _curvingOption;
    }

    TweenInnerType getStartValue() const {
        return _startValue;
    }

    TweenInnerType getEndValue() const {
        return _endValue;
    }

    const TimeRef &getStart() const {
        return _start;
    }

    const TimeRef &getEnd() const {
        return _end;
    }

    void Serialize(RType::Packer &packer) override {
        _startValue.Serialize(packer);
        _start.Serialize(packer);
        _endValue.Serialize(packer);
        _end.Serialize(packer);
        if (packer.getType() == RType::READ)
            _delta = _endValue - _startValue;
    }
};

template <>
class Tween<int> : public RType::ISerializable {

private:
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<ITweeningCurve> _curvingOption;

    int _startValue;
    int _endValue;

    TimeRef _start;
    TimeRef _end;

    int _delta;
    int _maxValue;

public:
    template <class TweeningCurve>
    Tween(std::shared_ptr<Timer> timer, int const &startValue, TimeRef const &start,
          int const &endValue, TimeRef const &end) : _timer(timer), _curvingOption(nullptr),
                                                                _startValue(startValue), _endValue(endValue), _start(start), _end(end),
                                                                _delta(_endValue - _startValue), _maxValue(std::numeric_limits<int>::max()){
        static_assert(std::is_base_of<ITweeningCurve, TweeningCurve>::value, "TweeningCurve must be a descendant of ITweeningCurve");
        _curvingOption = std::shared_ptr<TweeningCurve>(new TweeningCurve());
    }

    Tween(std::shared_ptr<Timer> timer, int const &startValue, TimeRef const &start,
          int const &endValue, TimeRef const &end, std::shared_ptr<ITweeningCurve> curve) : _timer(timer),_curvingOption(curve),
                                                                                                       _startValue(startValue), _endValue(endValue), _start(start), _end(end),
                                                                                                       _delta(_endValue - _startValue), _maxValue(std::numeric_limits<int>::max()){ }

    Tween() : _timer(nullptr),_curvingOption(nullptr),
              _startValue(), _endValue(), _start(), _end(),
              _delta(), _maxValue() { }

    int GetTweened() {
        auto now = _timer->getCurrent();
        auto currentTimeAsDouble = ((double)(now.getMilliseconds().count() - _start.getMilliseconds().count()) /
                                    ((double)(_end.getMilliseconds().count() - _start.getMilliseconds().count())));
        if (currentTimeAsDouble < 0)
            return _startValue;
        if (currentTimeAsDouble >= 1)
            return _endValue;

        return _startValue + (int)(_delta * _curvingOption->Curve(currentTimeAsDouble));
    }

    bool isPartOf(TimeRef const &timeRef) {
        return timeRef <= _end && timeRef >= _start;
    }

    const std::shared_ptr<ITweeningCurve> getCurvingOption() const {
        return _curvingOption;
    }

    int getStartValue() const {
        return _startValue;
    }

    int getEndValue() const {
        return _endValue;
    }

    const TimeRef &getStart() const {
        return _start;
    }

    const TimeRef &getEnd() const {
        return _end;
    }

    void Serialize(RType::Packer &packer) override {
        packer.Pack(_startValue);
        _start.Serialize(packer);
        packer.Pack(_endValue);
        _end.Serialize(packer);
        packer.Pack(_delta);
        packer.Pack(_maxValue);
    }
};


#endif //R_TYPE_TWEEN_HPP
