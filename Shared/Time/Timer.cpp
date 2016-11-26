//
// Created by hippolyteb on 11/22/16.
//

#include <Timer.hpp>
#include <iostream>

const std::chrono::time_point<std::chrono::system_clock> &Timer::getOrigin() const {
    return _origin;
}

TimeRef Timer::getCurrent() {
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto origin =std::chrono::time_point_cast<std::chrono::milliseconds>(_origin);
    if (now.time_since_epoch().count() < origin.time_since_epoch().count())
        return TimeRef(std::chrono::milliseconds(0));
    auto test = now - std::chrono::time_point_cast<std::chrono::milliseconds>(_origin);
    return TimeRef(test);
}

Timer::Timer(std::chrono::time_point<std::chrono::system_clock> origin) : _origin(origin) {

}

TimeRef Timer::getStart() {
    return TimeRef(std::chrono::milliseconds(0));
}

Timer::~Timer() {
    std::cout << "test" << std::endl;
}
