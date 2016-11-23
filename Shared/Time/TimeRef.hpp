//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMEREF_HPP
#define R_TYPE_TIMEREF_HPP

#include <chrono>

class TimeRef {
private:
    const std::chrono::milliseconds &_current;
public:
    TimeRef();
    TimeRef(const std::chrono::milliseconds &milliseconds);

    const std::chrono::milliseconds &getMilliseconds() const;
};


#endif //R_TYPE_TIMEREF_HPP
