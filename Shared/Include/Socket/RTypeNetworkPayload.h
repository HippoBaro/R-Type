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
        char *Buffer = nullptr;
        bool _shouldDelete = false;

        PackerContent(int lenght) : Buffer(new char[lenght]), _shouldDelete(true) {}
        PackerContent(char *data) : Buffer(data) {}

        PackerContent(const PackerContent& other) : Buffer(other.Buffer), _shouldDelete(other._shouldDelete) {}

        PackerContent& operator=(const PackerContent& other) {
            Buffer = other.Buffer;
            _shouldDelete = other._shouldDelete;
            return *this;
        }

        virtual ~PackerContent() {
            if (_shouldDelete)
                delete[](Buffer);
        }
    };

public:
    std::string Ip = std::string();
    std::shared_ptr<PackerContent> _payload;
    int Length;

    char *Payload = nullptr;

    RTypeNetworkPayload() : _payload(), Length() { }

    RTypeNetworkPayload(char *payload, int length) : _payload(std::make_shared<PackerContent>(payload)),
                                                     Length(length), Payload(_payload->Buffer) {}

    RTypeNetworkPayload(int length) : _payload(std::make_shared<PackerContent>(length)), Length(length), Payload(_payload->Buffer) { }

    RTypeNetworkPayload(char *payload, int length, std::string const &destination) : Ip(destination),
                                                                                     _payload(std::make_shared<PackerContent>(payload)),
                                                                                     Length(length),
                                                                                     Payload(_payload->Buffer){ }

    RTypeNetworkPayload(const RTypeNetworkPayload &payload) : Ip(payload.Ip),  _payload(payload._payload),
                                                              Length(payload.Length),
                                                              Payload(_payload->Buffer){ }

    RTypeNetworkPayload(const RType::Packer &packer) : _payload(std::make_shared<PackerContent>(packer.getBuffer())), Length(packer.getLength()),
                                                       Payload(_payload->Buffer){ }

    RTypeNetworkPayload(const RType::Packer &packer, std::string const &destination) : _payload(std::make_shared<PackerContent>(packer.getBuffer())),
                                                                                       Length(packer.getLength()),
                                                                                       Payload(_payload->Buffer){ }

    const RTypeNetworkPayload &operator=(const RTypeNetworkPayload &payload) { return *this; }
};

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
