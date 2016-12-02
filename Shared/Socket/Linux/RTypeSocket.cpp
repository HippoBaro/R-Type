//
// Created by pasteu_e on 28/11/16.
//

#include "RTypeSocket.hpp"

RTypeSocket::RTypeSocket(uint16_t port) : _socket(), _addr(), _port(port) {
    bzero(&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons(_port);
    CreateSocket();
}

RTypeSocket::RTypeSocket(const std::string &addr, uint16_t port) : _socket(), _addr(), _port(port) {
    bzero(&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    _addr.sin_port = htons(_port);
    CreateSocket();
}

RTypeSocket::~RTypeSocket() {
    close(_socket);
}

void RTypeSocket::CreateSocket() {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket < 0) {
        throw std::runtime_error(std::string("Create socket failed !"));
    }
}

void RTypeSocket::Bind() {
    if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
        throw std::runtime_error(std::string("Binding port failed !"));
    }
    if (fcntl(_socket, F_SETFL, O_NONBLOCK, 1) == -1) {
        throw std::runtime_error(std::string("Failed to set non-blocking socket !"));
    }
}

bool RTypeSocket::Receive(RTypeNetworkPayload &payload, size_t length) {
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

void RTypeSocket::Send(const std::string &payload) {
    if (sendto(_socket, payload.c_str(), payload.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr)) < 0) {
        // On ne throw pas ici car si il n'y a pas de server qui tourne lorseque le client tente de Send la function sendto renvera -1
        std::cerr << "Sending failed !" << std::endl;
    }
}