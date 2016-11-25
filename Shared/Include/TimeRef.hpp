//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMEREF_HPP
#define R_TYPE_TIMEREF_HPP

#include <chrono>

class TimeRef {
private:
    std::chrono::milliseconds _current;
public:
    TimeRef();
    TimeRef(const std::chrono::milliseconds &milliseconds);

    const std::chrono::milliseconds &getMilliseconds() const;

    TimeRef GetRelative(const std::chrono::milliseconds &milliseconds);

    friend bool operator<(const TimeRef &lhs, const TimeRef &rhs);
    friend bool operator>(const TimeRef &lhs, const TimeRef &rhs);
    friend bool operator<=(const TimeRef &lhs, const TimeRef &rhs);
    friend bool operator>=(const TimeRef &lhs, const TimeRef &rhs);

    friend bool operator==(const TimeRef &lhs, const TimeRef &rhs);
    friend bool operator!=(const TimeRef &lhs, const TimeRef &rhs);
};


#endif //R_TYPE_TIMEREF_HPP
