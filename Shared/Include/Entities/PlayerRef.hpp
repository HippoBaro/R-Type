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

public:
    PlayerRef(const uint8_t id, const std::string &address) : _id(id), _address(address) {}
};

#endif //R_TYPE_PLAYERREF_HPP
