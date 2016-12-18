//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMER_HPP
#define R_TYPE_TIMER_HPP

#include "TimeRef.hpp"
#include "IService.hpp"

class Timer : public IService {
private:
    std::chrono::time_point<std::chrono::steady_clock> _origin;

public:
    Timer(std::chrono::time_point<std::chrono::steady_clock> origin): _origin(origin) {}

    virtual ~Timer() {}

    const std::chrono::time_point<std::chrono::steady_clock> &getOrigin() const{
        return _origin;
    }

    TimeRef getCurrent() const {
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
        auto test = now - std::chrono::time_point_cast<std::chrono::milliseconds>(_origin);
        return TimeRef(test);
    }

    TimeRef getStart() {
        return TimeRef(0);
    }
};

#endif //R_TYPE_TIMER_HPP
