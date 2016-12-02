//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_IRTYPESOCKET_HPP
#define R_TYPE_IRTYPESOCKET_HPP

#include <iostream>
#include "RTypeNetworkPayload.h"
#include "RTypeSocketType.h"

class IRTypeSocket {
public:
    virtual ~IRTypeSocket() {}

    virtual void Bind() = 0;

    virtual bool Receive(RTypeNetworkPayload &, size_t) = 0;

    virtual void Send(const std::string &payload) = 0;
};

#endif //R_TYPE_IRTYPESOCKET_HPP
