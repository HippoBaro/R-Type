//
// Created by hippolyteb on 11/22/16.
//

#include "Timer.hpp"

Timer::Timer() : _origin() {}

void Timer::Reset() {
    _origin = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
}

const std::chrono::milliseconds &Timer::getOrigin() const {
    return _origin;
}

const TimeRef Timer::getCurrent() {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    return TimeRef(now - _origin);
}
