//
// Created by hippolyteb on 11/22/16.
//

#include <TimeRef.hpp>

TimeRef::TimeRef() : _current(std::chrono::milliseconds()) { }

TimeRef::TimeRef(const std::chrono::milliseconds &milliseconds) : _current(milliseconds) { }

const std::chrono::milliseconds &TimeRef::getMilliseconds() const {
    return _current;
}

bool operator<(const TimeRef &lhs, const TimeRef &rhs) {
    return lhs._current < rhs._current;
}

bool operator>(const TimeRef &lhs, const TimeRef &rhs) {
    return rhs < lhs;
}

bool operator<=(const TimeRef &lhs, const TimeRef &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const TimeRef &lhs, const TimeRef &rhs) {
    return !(lhs < rhs);
}

bool operator==(const TimeRef &lhs, const TimeRef &rhs) {
    return lhs._current == rhs._current;
}

bool operator!=(const TimeRef &lhs, const TimeRef &rhs) {
    return !(rhs == lhs);
}

TimeRef TimeRef::GetRelative(const std::chrono::milliseconds &milliseconds) {
    return TimeRef(_current + milliseconds);
}
