//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_RTYPESOCKETLINUX_HPP
#define R_TYPE_RTYPESOCKETLINUX_HPP

#include "IRTypeSocket.hpp"
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include "RTypeNetworkPayload.h"

class RTypeSocket : public IRTypeSocket {
private:
    int _socket;
    struct sockaddr_in _addr;
    uint16_t _port;

private:
    void CreateSocket();

public:
    RTypeSocket(uint16_t port);

    RTypeSocket(const std::string &addr, uint16_t port);

    virtual ~RTypeSocket();

    void Bind() override final;

    void Receive(RTypeNetworkPayload &payload, size_t length) override final;

    void Send(const std::string &payload) override final;

};


#endif //R_TYPE_RTYPESOCKETLINUX_HPP
