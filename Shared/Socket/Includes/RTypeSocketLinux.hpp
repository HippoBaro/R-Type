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

constexpr uint16_t port() { return 5673; }

class RTypeSocketLinux : public IRTypeSocket {
private:
    int _socket;
    struct sockaddr_in _addr;

private:
    void CreateSocket();

public:
    RTypeSocketLinux();

    RTypeSocketLinux(const std::string &addr);

    virtual ~RTypeSocketLinux();

    void Bind() override final;

    void Receive(RTypeNetworkPayload &payload, size_t length) override final;

    void Send(const std::string &payload) override final;

};


#endif //R_TYPE_RTYPESOCKETLINUX_HPP
