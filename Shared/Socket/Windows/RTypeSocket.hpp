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

template<SocketType type>
class RTypeSocket : public IRTypeSocket {
};

template<>
class RTypeSocket<UDP> : public IRTypeSocket {
private:
    SOCKET _socket;
    SOCKADDR_IN _addr;
    uint16_t _port;

private:
    void CreateSocket() {
        WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);
        if (err < 0) {
            throw std::runtime_error(std::string("WSAStartup failed !"));
        }
        _socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (_socket < 0) {
            throw std::runtime_error(std::string("Create socket failed !"));
        }
    }

public:
    RTypeSocket(uint16_t port) : _socket(), _addr(), _port(port) {
        memset((&_addr), '\0', (sizeof(_addr)));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        _addr.sin_port = htons(_port);
        CreateSocket();
    }

    RTypeSocket(const std::string &addr, uint16_t port) : _socket(), _addr(), _port(port) {
        memset((&_addr), '\0', (sizeof(_addr)));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = inet_addr(addr.c_str());
        _addr.sin_port = htons(_port);
        CreateSocket();
    }

    ~RTypeSocket() {
		closesocket(_socket);
        WSACleanup();
    }

    void Bind() override final {
        if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
            throw std::runtime_error(std::string("Binding port failed !"));
        }
        DWORD nonBlocking = 1;
        if (ioctlsocket(_socket, FIONBIO, &nonBlocking) != 0) {
            throw std::runtime_error(std::string("Failed to set non-blocking socket !"));
        }
    }

    bool Connect() override {
        return false;
    }

    std::unique_ptr<IRTypeSocket> Accept() override {
        return nullptr;
    }

    bool Receive(RTypeNetworkPayload &payload, size_t length) override final {
        SOCKADDR_IN  clientAddr;
        int lengthSockAddr = sizeof(clientAddr);

        char *buffer = (char *) malloc(sizeof(char) * length);
        memset((buffer), '\0', (length));
        SSIZE_T data = recvfrom(_socket, buffer, length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
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
    SocketIdentity _identity;
    SOCKET _socket;
    SOCKADDR_IN _addrServer;
    SOCKADDR_IN _addrClient;
    uint16_t _port;

private:
    void CreateSocket() {
        WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);
        if (err < 0) {
            throw std::runtime_error(std::string("WSAStartup failed !"));
        }
        if (_identity == Server) {
            _socket = socket(PF_INET, SOCK_STREAM, 0);
            if (_socket < 0) {
                throw std::runtime_error(std::string("Create socket failed !"));
            } else {
                const char opt = 1;
                setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            }
        } else if (_identity == Client) {
            _socket = socket(AF_INET, SOCK_STREAM, 0);
            if (_socket < 0) {
                throw std::runtime_error(std::string("Create socket failed !"));
            }
        }
    }

public:
    RTypeSocket(uint16_t port) : _identity(), _socket(), _addrServer(), _addrClient(), _port(port) {
        _identity = Server;
        memset((&_addrServer), '\0', (sizeof(_addrServer)));
        _addrServer.sin_family = AF_INET;
        _addrServer.sin_addr.s_addr = htons(INADDR_ANY);
        _addrServer.sin_port = htons(_port);
        CreateSocket();
    }

    RTypeSocket(const std::string &addr, uint16_t port) : _identity(), _socket(), _addrServer(), _addrClient(), _port(port) {
        _identity = Client;
        memset((&_addrClient), '\0', (sizeof(_addrClient)));
        _addrClient.sin_family = AF_INET;
        _addrClient.sin_addr.s_addr = htons(INADDR_ANY);
        _addrClient.sin_port = htons(0);
        memset((&_addrServer), '\0', (sizeof(_addrServer)));
        _addrServer.sin_family = AF_INET;
        _addrServer.sin_addr.s_addr = inet_addr(addr.c_str());
        _addrServer.sin_port = htons(_port);
        CreateSocket();
    }

    RTypeSocket(SOCKET socket, SOCKADDR_IN addrClient) : _identity(), _socket(socket), _addrServer(), _addrClient(addrClient), _port() {}

    ~RTypeSocket() {
		closesocket(_socket);
        WSACleanup();
    }

    void Bind() override final {
        if (_identity == Server) {
            if (bind(_socket, (struct sockaddr *) &_addrServer, sizeof(_addrServer))) {
                throw std::runtime_error(std::string("Binding port failed !"));
            }
            if (listen(_socket, 20)) {
                throw std::runtime_error(std::string("Server Listen Failed !"));
            }
        } else if (_identity == Client) {
            if (bind(_socket, (struct sockaddr *) &_addrClient, sizeof(_addrClient))) {
                throw std::runtime_error(std::string("Binding port failed !"));
            }
        }
    }

    bool Connect() override final {
        if (connect(_socket, (struct sockaddr *) &_addrServer, sizeof(_addrServer)) < 0) {
            std::cerr << "Connect failed !" << std::endl;
            return false;
        }
        return true;
    }

    std::unique_ptr<IRTypeSocket> Accept() override final {
        struct sockaddr_in clientAddr;
        int length = sizeof(clientAddr);
        int client = accept(_socket, (struct sockaddr *) &clientAddr, &length);
        if (client < 0) {
            std::cerr << "Server Accept Failed !" << std::endl;
            return nullptr;
        }
        return std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(client, clientAddr));
    }

    bool Receive(RTypeNetworkPayload &payload, size_t length) override final {
        char *buffer = (char *) malloc(sizeof(char) * length);
        memset((buffer), '\0', (length));
        SSIZE_T data = recv(_socket,buffer,length,0);
        if (data == -1) {
            free(buffer);
            return false;
        } else {
            buffer[data] = '\0';
            payload.Ip = std::string(inet_ntoa(_addrClient.sin_addr));
            payload.Payload = std::string(buffer);
            free(buffer);
            return true;
        }
    }

    void Send(const std::string &payload) override final {
        if (send(_socket, payload.c_str(), payload.size(), 0) < 0) {
            std::cerr << "Sending failed !" << std::endl;
        }
    }
};

#endif //R_TYPE_RTYPESOCKETWINDOWS_HPP
