//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_TWEEN_HPP
#define R_TYPE_TWEEN_HPP


#include <memory>
#include <tgmath.h>
#include "ITweeningCurve.hpp"
#include "Timer.hpp"

template <typename TweenInnerType>
class Tween {

private:
    std::shared_ptr<Timer> _timer;
    std::shared_ptr<ITweeningCurve> _curvingOption;

    TweenInnerType _startValue;
    TweenInnerType _endValue;

    TimeRef _start;
    TimeRef _end;

    TweenInnerType _delta;
    TweenInnerType _maxValue;

public:
    template <class TweeningCurve>
    Tween(std::shared_ptr<Timer> &timer, TweenInnerType const &startValue, TimeRef const &start,
          TweenInnerType const &endValue, TimeRef const &end) : _timer(timer), _curvingOption(nullptr),
                                                                _startValue(startValue), _endValue(endValue), _start(start), _end(end),
                                                                _delta(_endValue - _startValue), _maxValue(std::numeric_limits<TweenInnerType>::max()){
        static_assert(std::is_base_of<ITweeningCurve, TweeningCurve>::value, "TweeningCurve must be a descendant of ITweeningCurve");
        _curvingOption = std::unique_ptr<ITweeningCurve>(new TweeningCurve());
    }

    Tween(std::shared_ptr<Timer> &timer, TweenInnerType const &startValue, TimeRef const &start,
         TweenInnerType const &endValue, TimeRef const &end, ITweeningCurve *curve) : _timer(timer),_curvingOption(std::shared_ptr<ITweeningCurve>(curve)),
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

        TweenInnerType newValue = _startValue + static_cast<TweenInnerType>(fmod(_curvingOption->Curve(currentTimeAsDouble) * _delta, _maxValue));
        return newValue;
    }
};

#endif //R_TYPE_TWEEN_HPP
