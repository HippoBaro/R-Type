//
// Created by hippolyteb on 12/1/16.
//

#include <cstdint>
#include "GameInstance.hpp"

GameInstance::GameInstance(uint16_t id, std::string const &partition, std::chrono::steady_clock::time_point const &origin) : _id(id) {
    _timer = std::make_shared<Timer>(origin);

}
