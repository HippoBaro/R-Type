//
// Created by pasteu_e on 29/11/16.
//

#ifndef R_TYPE_RTYPENETWORKPAYLOAD_H
#define R_TYPE_RTYPENETWORKPAYLOAD_H

#include <iostream>

class RTypeNetworkPayload {
public:
    std::string Ip;
    std::string Payload;

    RTypeNetworkPayload(std::string const &ip = "", std::string const &payload = "") : Ip(ip), Payload(payload) {};
};

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
