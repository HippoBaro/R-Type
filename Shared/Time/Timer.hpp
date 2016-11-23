//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMER_HPP
#define R_TYPE_TIMER_HPP

#include "TimeRef.hpp"

class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> _origin;

public:
    Timer(std::chrono::time_point<std::chrono::system_clock> origin);

    const std::chrono::time_point<std::chrono::system_clock> &getOrigin() const;
    const TimeRef getCurrent();
};

#endif //R_TYPE_TIMER_HPP