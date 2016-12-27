//
// Created by hippolyteb on 12/2/16.
//

#ifndef R_TYPE_PLAYERREF_HPP
#define R_TYPE_PLAYERREF_HPP

#include <cstdint>
#include <string>

class PlayerRef {
private:
    const uint8_t _id;
    const std::string _address;
    bool _isReady = false;

public:
    PlayerRef(const uint8_t id, const std::string &address) : _id(id), _address(address) {}

    PlayerRef(const uint8_t _id, const std::string &_address, bool _isReady) : _id(_id), _address(_address), _isReady(_isReady) {}

    bool IsReady() const {
        return _isReady;
    }

    void SetReady(bool isReady) {
        _isReady = isReady;
    }

    const std::string &GetAddress() const {
        return _address;
    }

    uint8_t GetId() const {
        return _id;
    }

};

#endif //R_TYPE_PLAYERREF_HPP
