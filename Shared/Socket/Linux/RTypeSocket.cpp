//
// Created by pasteu_e on 28/11/16.
//

#include "RTypeSocket.hpp"

RTypeSocket::RTypeSocket() :_socket(), _addr() {
    bzero(&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons(port());
    CreateSocket();
}

RTypeSocket::RTypeSocket(const std::string &addr) :_socket(), _addr() {
    bzero(&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    _addr.sin_port = htons(port());
    CreateSocket();
}

RTypeSocket::~RTypeSocket() {
    close(_socket);
}

void RTypeSocket::CreateSocket() {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket < 0) {
        std::cerr << "Create socket failed ! " << std::endl;
    }
}

void RTypeSocket::Bind() {
    if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
        std::cerr << "Binding port " << port() << " failed !" << std::endl;
    }
    if (fcntl(_socket, F_SETFL, O_NONBLOCK, 1) == -1) {
        std::cerr << "Failed to set non-blocking socket !" << std::endl;
    }
}

void RTypeSocket::Receive(RTypeNetworkPayload &payload, size_t length) {
    struct sockaddr_in clientAddr;
    socklen_t lengthSockAddr = sizeof(clientAddr);

    char *buffer = (char *) malloc(sizeof(char) * length);
    bzero(buffer, length);
    ssize_t data = recvfrom(_socket, buffer, length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
    if (data == -1) {
        payload._isEmpty = true;
        payload._ip = "";
        payload._payload = "";
        free(buffer);
    } else {
        buffer[data] = '\0';
        payload._isEmpty = false;
        payload._ip = std::string(inet_ntoa(clientAddr.sin_addr));
        payload._payload = std::string(buffer);
        free(buffer);
    }
}

void RTypeSocket::Send(const std::string &payload) {
    if (sendto(_socket, payload.c_str(), payload.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr)) < 0) {
        std::cerr << "Sending failed !" << std::endl;
    }
}