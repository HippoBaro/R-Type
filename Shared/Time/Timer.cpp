//
// Created by hippolyteb on 11/22/16.
//

#include "Timer.hpp"

const std::chrono::time_point<std::chrono::system_clock> &Timer::getOrigin() const {
    return _origin;
}

const TimeRef Timer::getCurrent() {
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto test = now - std::chrono::time_point_cast<std::chrono::milliseconds>(_origin);
    return TimeRef(test);
}

Timer::Timer(std::chrono::time_point<std::chrono::system_clock> origin) : _origin(origin) {

}