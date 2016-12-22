//
// Created by pasteu_e on 29/11/16.
//

#ifndef R_TYPE_RTYPENETWORKPAYLOAD_H
#define R_TYPE_RTYPENETWORKPAYLOAD_H

#include <iostream>

class RTypeNetworkPayload {
private:
    bool _alloc = false;

public:
    std::string Ip = std::string();
    char *Payload;
    int Length;

    RTypeNetworkPayload() : Payload(), Length() {}
    RTypeNetworkPayload(char *payload, int length) : Payload(payload), Length(length) {}
    RTypeNetworkPayload(int length) : _alloc(true), Payload(new char[length]), Length(length) {}
    RTypeNetworkPayload(char *payload, int length, std::string const &destination) : Ip(destination), Payload(payload), Length(length) {}
    RTypeNetworkPayload(const RTypeNetworkPayload& payload) : _alloc(payload._alloc), Ip(payload.Ip), Payload(payload.Payload), Length(payload.Length) {}
    const RTypeNetworkPayload& operator=(const RTypeNetworkPayload& payload) { return *this; }

    virtual ~RTypeNetworkPayload() {
		//if (_alloc)
		//	delete[] Payload;
    }
};

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
