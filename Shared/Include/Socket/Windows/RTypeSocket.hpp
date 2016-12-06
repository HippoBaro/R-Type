//
// Created by pasteu_e on 30/11/16.
//

#ifndef R_TYPE_RTYPESOCKETWINDOWS_HPP
#define R_TYPE_RTYPESOCKETWINDOWS_HPP

#include <Socket/IRTypeSocket.hpp>
#include <fcntl.h>
#include <cstdlib>
#include <winsock.h>
#include <stdexcept>
#include <Socket/RTypeNetworkPayload.h>
#include <Socket/Enum/RTypeSocketType.h>

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

    bool Receive(RTypeNetworkPayload &payload) override final {
        SOCKADDR_IN  clientAddr;
        int lengthSockAddr = sizeof(clientAddr);

        memset((payload.Payload), '\0', (size_t) (payload.Length));
        SSIZE_T data = recvfrom(_socket, payload.Payload, payload.Length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
        if (data == -1) {
            return false;
        } else {
            payload.Ip = std::string(inet_ntoa(clientAddr.sin_addr));
            return true;
        }
    }

    bool Send(const RTypeNetworkPayload &payload) override final {
        return sendto(_socket, payload.Payload, payload.Length, 0, (struct sockaddr *) &_addr, sizeof(_addr)) >= 0;
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

    RTypeSocket(SOCKET socket, SOCKADDR_IN addrClient) : _identity(), _socket(socket), _addrServer(), _addrClient(addrClient), _port() {}

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
        return connect(_socket, (struct sockaddr *) &_addrServer, sizeof(_addrServer)) >= 0;
    }

    std::unique_ptr<IRTypeSocket> Accept() override final {
        struct sockaddr_in clientAddr;
        int length = sizeof(clientAddr);
        SOCKET client = accept(_socket, (struct sockaddr *) &clientAddr, &length);
        if (client < 0) {
            return nullptr;
        }
        return std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(client, clientAddr));
    }

    bool Receive(RTypeNetworkPayload &payload) override final {
        memset((payload.Payload), '\0', (size_t) (payload.Length));
        SSIZE_T data = recv(_socket, payload.Payload, payload.Length,0);
        if (data == -1) {
            return false;
        } else {
            payload.Ip = std::string(inet_ntoa(_addrClient.sin_addr));
            return true;
        }
    }

    bool Send(const RTypeNetworkPayload &payload) override final {
        return send(_socket, payload.Payload, payload.Length, 0) >= 0;
    }
};

#endif //R_TYPE_RTYPESOCKETWINDOWS_HPP
