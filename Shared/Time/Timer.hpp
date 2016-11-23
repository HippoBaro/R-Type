//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMER_HPP
#define R_TYPE_TIMER_HPP

#include "TimeRef.hpp"

class Timer {
private:
    std::chrono::milliseconds _origin;

public:
    Timer();
    void Reset();
    const std::chrono::milliseconds &getOrigin() const;
    const TimeRef getCurrent();
};


#endif //R_TYPE_TIMER_HPP
