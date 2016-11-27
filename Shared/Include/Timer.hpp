//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMER_HPP
#define R_TYPE_TIMER_HPP

#include "TimeRef.hpp"
#include "IService.hpp"

class Timer : public IService {
private:
    std::chrono::time_point<std::chrono::system_clock> _origin;

public:
    Timer(std::chrono::time_point<std::chrono::system_clock> origin);

    virtual ~Timer();

    const std::chrono::time_point<std::chrono::system_clock> &getOrigin() const;
    TimeRef getCurrent();
    TimeRef getStart();
};

#endif //R_TYPE_TIMER_HPP
