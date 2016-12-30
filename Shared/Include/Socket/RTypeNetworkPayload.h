//
// Created by pasteu_e on 29/11/16.
//

#ifndef R_TYPE_RTYPENETWORKPAYLOAD_H
#define R_TYPE_RTYPENETWORKPAYLOAD_H

#include <iostream>
#include <Serializer/Packer.hpp>

class RTypeNetworkPayload {
private:
    class PackerContent {
    public:
        char *_buffer = nullptr;
        bool _shouldDelete = false;

        PackerContent(int length) : _buffer(new char[length]), _shouldDelete(true) {}

        PackerContent(char *data, int length) : _buffer(new char[length]), _shouldDelete(true) {
            memcpy(_buffer, data, (size_t)length);
        }

        PackerContent(const PackerContent& other) : _buffer(other._buffer), _shouldDelete(other._shouldDelete) {}

        PackerContent& operator=(const PackerContent& other) {
            _buffer = other._buffer;
            _shouldDelete = other._shouldDelete;
            return *this;
        }

        virtual ~PackerContent() {
            if (_shouldDelete)
                delete[](_buffer);
        }
    };

public:
    std::string Ip = std::string();
    std::shared_ptr<PackerContent> _payload;
    int Length;

    char *Payload = nullptr;

    RTypeNetworkPayload() : _payload(), Length() { }

    RTypeNetworkPayload(char *payload, int length) : _payload(std::make_shared<PackerContent>(payload, length)),
                                                     Length(length), Payload(_payload->_buffer) {}

    RTypeNetworkPayload(int length) : _payload(std::make_shared<PackerContent>(length)), Length(length), Payload(_payload->_buffer) { }

    RTypeNetworkPayload(char *payload, int length, std::string const &destination) : Ip(destination),
                                                                                     _payload(std::make_shared<PackerContent>(payload, length)),
                                                                                     Length(length),
                                                                                     Payload(_payload->_buffer){ }

    RTypeNetworkPayload(const RTypeNetworkPayload &payload) : Ip(payload.Ip),  _payload(payload._payload),
                                                              Length(payload.Length),
                                                              Payload(_payload->_buffer){ }

    RTypeNetworkPayload(const RType::Packer &packer) : _payload(std::make_shared<PackerContent>(packer.getBuffer(), packer.getLength())), Length(packer.getLength()),
                                                       Payload(_payload->_buffer){ }

    RTypeNetworkPayload(const RType::Packer &packer, std::string const &destination) : _payload(std::make_shared<PackerContent>(packer.getBuffer(), packer.getLength())),
                                                                                       Length(packer.getLength()),
                                                                                       Payload(_payload->_buffer){ }

    const RTypeNetworkPayload &operator=(const RTypeNetworkPayload &payload) { return *this; }
};

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
