//
// Created by hippolyteb on 11/22/16.
//

#include <chrono>
#include "TimeRef.hpp"

TimeRef::TimeRef() : _current(std::chrono::milliseconds()) {

}

TimeRef::TimeRef(const std::chrono::milliseconds &milliseconds) : _current(milliseconds) {

}

const std::chrono::milliseconds &TimeRef::getMilliseconds() const {
    return _current;
}
