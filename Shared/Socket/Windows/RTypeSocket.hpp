//
// Created by pasteu_e on 30/11/16.
//

#ifndef R_TYPE_RTYPESOCKETWINDOWS_HPP
#define R_TYPE_RTYPESOCKETWINDOWS_HPP

#include "IRTypeSocket.hpp"
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include <winsock.h>
#include <stdexcept>
#include "RTypeNetworkPayload.h"


class RTypeSocket : public IRTypeSocket {
private:
    SOCKET _socket;
    SOCKADDR_IN _addr;
    uint16_t _port;

private:
    void CreateSocket();

public:
    RTypeSocket(uint16_t port);

    RTypeSocket(const std::string &addr, uint16_t port);

    virtual ~RTypeSocket();

    void Bind() override final;

    bool Receive(RTypeNetworkPayload &payload, size_t length) override final;

    void Send(const std::string &payload) override final;

};


#endif //R_TYPE_RTYPESOCKETWINDOWS_HPP
