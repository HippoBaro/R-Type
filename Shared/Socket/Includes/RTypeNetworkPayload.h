//
// Created by pasteu_e on 29/11/16.
//

#ifndef R_TYPE_RTYPENETWORKPAYLOAD_H
#define R_TYPE_RTYPENETWORKPAYLOAD_H

#include <iostream>

typedef struct {
    bool _isEmpty = true;
    std::string _ip = "";
    std::string _payload = "";
} RTypeNetworkPayload;

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
