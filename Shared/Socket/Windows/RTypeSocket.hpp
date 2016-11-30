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
#include "RTypeNetworkPayload.h"

constexpr uint16_t port() { return 5673; }

class RTypeSocket : public IRTypeSocket {
private:
    SOCKET _socket;
    SOCKADDR_IN _addr;

private:
    void CreateSocket();

public:
    RTypeSocket();

    RTypeSocket(const std::string &addr);

    virtual ~RTypeSocket();

    void Bind() override final;

    void Receive(RTypeNetworkPayload &payload, size_t length) override final;

    void Send(const std::string &payload) override final;

};


#endif //R_TYPE_RTYPESOCKETWINDOWS_HPP
