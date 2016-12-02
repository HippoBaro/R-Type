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
#include <stdexcept>
#include "RTypeNetworkPayload.h"

template<SocketType type>
class RTypeSocket : public IRTypeSocket {
};

template<>
class RTypeSocket<UDP> : public IRTypeSocket {
private:
    int _socket;
    struct sockaddr_in _addr;
    uint16_t _port;

private:
    void CreateSocket() {
        _socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (_socket < 0) {
            throw std::runtime_error(std::string("Create socket failed !"));
        }
    }

public:
    RTypeSocket(uint16_t port) : _socket(), _addr(), _port(port) {
        bzero(&_addr, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        _addr.sin_port = htons(_port);
        CreateSocket();
    }

    RTypeSocket(const std::string &addr, uint16_t port) : _socket(), _addr(), _port(port) {
        bzero(&_addr, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = inet_addr(addr.c_str());
        _addr.sin_port = htons(_port);
        CreateSocket();
    }

    ~RTypeSocket() {
        close(_socket);
    }

    void Bind() override final {
        if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
            throw std::runtime_error(std::string("Binding port failed !"));
        }
        if (fcntl(_socket, F_SETFL, O_NONBLOCK, 1) == -1) {
            throw std::runtime_error(std::string("Failed to set non-blocking socket !"));
        }
    }

    bool Receive(RTypeNetworkPayload &payload, size_t length) override final {
        struct sockaddr_in clientAddr;
        socklen_t lengthSockAddr = sizeof(clientAddr);

        char *buffer = (char *) malloc(sizeof(char) * length);
        bzero(buffer, length);
        ssize_t data = recvfrom(_socket, buffer, length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
        if (data == -1) {
            free(buffer);
            return false;
        } else {
            buffer[data] = '\0';
            payload.Ip = std::string(inet_ntoa(clientAddr.sin_addr));
            payload.Payload = std::string(buffer);
            free(buffer);
            return true;
        }
    }

    void Send(const std::string &payload) override final {
        if (sendto(_socket, payload.c_str(), payload.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr)) < 0) {
            // On ne throw pas ici car si il n'y a pas de server qui tourne lorseque le client tente de Send la function sendto renvera -1
            std::cerr << "Sending failed !" << std::endl;
        }
    }

};

template<>
class RTypeSocket<TCP> : public IRTypeSocket {
private:
    int _socket;
    struct sockaddr_in _addr;
    uint16_t _port;

public:
    RTypeSocket(uint16_t port) : _socket(), _addr(), _port(port) {}
};

#endif //R_TYPE_RTYPESOCKETLINUX_HPP
