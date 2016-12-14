//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TIMEREF_HPP
#define R_TYPE_TIMEREF_HPP

#include <chrono>
#include <Serializer/ISerializable.hpp>

class TimeRef : public RType::ISerializable {
private:
    uint32_t _current;
public:

    TimeRef() : _current(0) {}

    TimeRef(const std::chrono::milliseconds &milliseconds) : _current((uint32_t) milliseconds.count()) {}
    TimeRef(const long milliseconds) : _current((uint32_t) milliseconds) {}

    const std::chrono::milliseconds getMilliseconds() const {
        return std::chrono::milliseconds(_current);
    }

    TimeRef GetRelative(const std::chrono::milliseconds &milliseconds) {
        return TimeRef(_current + milliseconds.count());
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

    void Serialize(RType::Packer &packer) override {
        packer.Pack(_current);
    }
};


#endif //R_TYPE_TIMEREF_HPP
