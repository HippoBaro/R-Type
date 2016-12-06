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

    TimeRef() : _current(std::chrono::milliseconds()) {}

    TimeRef(const std::chrono::milliseconds &milliseconds) : _current(milliseconds) {}

    const std::chrono::milliseconds &getMilliseconds() const {
        return _current;
    }

    TimeRef GetRelative(const std::chrono::milliseconds &milliseconds) {
        return TimeRef(_current + milliseconds);
    }

    friend bool operator<(const TimeRef &lhs, const TimeRef &rhs) {
        return lhs._current < rhs._current;
    }

    friend bool operator>(const TimeRef &lhs, const TimeRef &rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const TimeRef &lhs, const TimeRef &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const TimeRef &lhs, const TimeRef &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const TimeRef &lhs, const TimeRef &rhs){
        return lhs._current == rhs._current;
    }

    friend bool operator!=(const TimeRef &lhs, const TimeRef &rhs) {
        return !(rhs == lhs);
    }
};


#endif //R_TYPE_TIMEREF_HPP
