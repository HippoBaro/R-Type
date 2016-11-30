//
// Created by pasteu_e on 30/11/16.
//

#ifndef R_TYPE_RTYPESOCKETWINDOWS_HPP
#define R_TYPE_RTYPESOCKETWINDOWS_HPP

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

class RTypeSocketWindows : public IRTypeSocket {
private:
    int _socket;
    struct sockaddr_in _addr;

private:
    void CreateSocket();

public:
    RTypeSocketWindows();

    RTypeSocketWindows(const std::string &addr);

    virtual ~RTypeSocketWindows();

    void Bind() override final;

    void Receive(RTypeNetworkPayload &payload, size_t length) override final;

    void Send(const std::string &payload) override final;

};


#endif //R_TYPE_RTYPESOCKETWINDOWS_HPP
