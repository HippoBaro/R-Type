//
// Created by hippolyteb on 12/2/16.
//

#ifndef R_TYPE_PLAYERREF_HPP
#define R_TYPE_PLAYERREF_HPP

#include <cstdint>
#include <string>
#include <Serializer/ISerializable.hpp>

class PlayerRef : public RType::ISerializable {
private:
    uint8_t _id;
    std::string _address;
    bool _isReady = false;

public:
    PlayerRef() : _id(0), _address() {};

    PlayerRef(const uint8_t id, const std::string &address) : _id(id), _address(address) {}

    PlayerRef(const uint8_t _id, const std::string &_address, bool _isReady) : _id(_id), _address(_address), _isReady(_isReady) {}

    bool isReady() const {
        return _isReady;
    }

    void setReady(const bool isReady) {
        _isReady = isReady;
    }

    const std::string &GetAddress() const {
        return _address;
    }

    uint8_t GetId() const {
        return _id;
    }

    virtual void Serialize(RType::Packer &packer) override final {
        packer.Pack(_id);
        packer.Pack(_address);
        packer.Pack(_isReady);
    }
};

#endif //R_TYPE_PLAYERREF_HPP
