//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_RTYPESOCKETLINUX_HPP
#define R_TYPE_RTYPESOCKETLINUX_HPP

#if APPLE
#define POLLRDHUP POLLHUP
#endif

#include <Socket/IRTypeSocket.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <Socket/RTypeNetworkPayload.h>
#include <cstring>
#include <unistd.h>
#include <poll.h>

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

    void *GetNativeSocket() override {
        return (void *) &_socket;
    }

    void Bind() override final {
        if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
            throw std::runtime_error(std::string("Binding port failed !"));
        }
        if (fcntl(_socket, F_SETFL, O_NONBLOCK, 1) == -1) {
            throw std::runtime_error(std::string("Failed to set non-blocking socket !"));
        }
    }

    bool Connect() override {
        return false;
    }

    std::shared_ptr<IRTypeSocket> Accept() override {
        return nullptr;
    }

    bool PoolEventOnSocket(SocketEvent evt, int timeout) override {
        return false;
    }

    bool Receive(RTypeNetworkPayload &payload) override final {
        struct sockaddr_in clientAddr;
        socklen_t lengthSockAddr = sizeof(clientAddr);

        bzero(payload.Payload, (size_t) payload.Length);
        ssize_t data = recvfrom(_socket, payload.Payload, (size_t) payload.Length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
        if (data == -1) {
            return false;
        } else {
            payload.Ip = std::string(inet_ntoa(clientAddr.sin_addr));
            return true;
        }
    }

    bool Send(const RTypeNetworkPayload &payload) override final {
        return sendto(_socket, payload.Payload, (size_t) payload.Length, 0, (struct sockaddr *) &_addr, sizeof(_addr)) >= 0;
    }
};

template<>
class RTypeSocket<TCP> : public IRTypeSocket {
private:
    SocketIdentity _identity;
    int _socket;
    struct sockaddr_in _addrServer;
    struct sockaddr_in _addrClient;
    uint16_t _port;

private:
    void CreateSocket() {
        if (_identity == Server) {
            _socket = socket(AF_INET, SOCK_STREAM, 0);
            if (_socket < 0) {
                throw std::runtime_error(std::string("Create socket failed !"));
            } else {
                int opt = 1;
                setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            }
        } else if (_identity == Client) {
            _socket = socket(AF_INET, SOCK_STREAM, 0);
            if (_socket < 0) {
                throw std::runtime_error(std::string("Create socket failed !"));
            }
        }
    }

    RTypeSocket(int socket, struct sockaddr_in addrClient) : _identity(), _socket(socket), _addrServer(), _addrClient(addrClient), _port() {}

public:
    RTypeSocket(uint16_t port) : _identity(), _socket(), _addrServer(), _addrClient(), _port(port) {
        _identity = Server;
        bzero(&_addrServer, sizeof(_addrServer));
        _addrServer.sin_family = AF_INET;
        _addrServer.sin_addr.s_addr = htons(INADDR_ANY);
        _addrServer.sin_port = htons(_port);
        CreateSocket();
    }

    RTypeSocket(const std::string &addr, uint16_t port) : _identity(), _socket(), _addrServer(), _addrClient(), _port(port) {
        _identity = Client;
        bzero(&_addrClient, sizeof(_addrClient));
        _addrClient.sin_family = AF_INET;
        _addrClient.sin_addr.s_addr = htons(INADDR_ANY);
        _addrClient.sin_port = htons(0);

        bzero(&_addrServer, sizeof(_addrServer));
        _addrServer.sin_family = AF_INET;
        if (inet_aton(addr.c_str(), &_addrServer.sin_addr) == 0) {
            throw std::runtime_error(std::string("Server IP Address Error !"));
        }
        _addrServer.sin_port = htons(_port);
        CreateSocket();
    }

    ~RTypeSocket() {
        close(_socket);
    }

    void *GetNativeSocket() override {
        return (void *) &_socket;
    }

    void Bind() override final {
        if (_identity == Server) {
            if (bind(_socket, (struct sockaddr *) &_addrServer, sizeof(_addrServer))) {
                throw std::runtime_error(std::string("Binding port failed !"));
            }
            if (listen(_socket, 20)) {
                throw std::runtime_error(std::string("Server Listen Failed !"));
            }
        }
    }

    bool Connect() override final {
        return connect(_socket, (struct sockaddr *) &_addrServer, sizeof(_addrServer)) >= 0;
    }

    std::shared_ptr<IRTypeSocket> Accept() override final {
        struct sockaddr_in clientAddr;
        socklen_t length = sizeof(clientAddr);
        int client = accept(_socket, (struct sockaddr *) &clientAddr, &length);
        if (client < 0) {
            return nullptr;
        }
        return std::shared_ptr<IRTypeSocket>(new RTypeSocket<TCP>(client, clientAddr));
    }

    bool PoolEventOnSocket(SocketEvent evt, int timeout) override {
        struct pollfd pfds[1];
        pfds[0].fd = *((int *) GetNativeSocket());
        switch (evt) {
            case SOCKET_CLOSED:
                pfds[0].events = POLLRDHUP;
                break;
            case DATA_INCOMING:
                pfds[0].events = POLLIN;
                break;
            case SOMEONE_LISTENING:
                pfds[0].events = POLLOUT;
                break;
        }
        if (poll(pfds, 1, timeout) > 0) {
            switch (evt) {
                case SOCKET_CLOSED:
                    if (pfds[0].revents == POLLRDHUP)
                        return true;
                    break;
                case DATA_INCOMING:
                    if (pfds[0].revents == POLLIN)
                        return true;
                    break;
                case SOMEONE_LISTENING:
                    if (pfds[0].revents == POLLOUT)
                        return true;
                    break;
            }
        }
        return  false;
    }

    bool Receive(RTypeNetworkPayload &payload) override final {
        bzero(payload.Payload, (size_t) payload.Length);
        ssize_t data = recv(_socket, payload.Payload, (size_t) payload.Length, 0);
        if (data == -1) {
            return false;
        } else {
            payload.Ip = std::string(inet_ntoa(_addrClient.sin_addr));
            return true;
        }
    }

    bool Send(const RTypeNetworkPayload &payload) override final {
        return send(_socket, payload.Payload, (size_t) payload.Length, 0) >= 0;
    }

};

#endif //R_TYPE_RTYPESOCKETLINUX_HPP
