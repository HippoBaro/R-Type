//
// Created by pasteu_e on 30/11/16.
//

#include "RTypeSocket.hpp"

RTypeSocket::RTypeSocket() : _socket(), _addr() {
    memset((&_addr), '\0', (sizeof(_addr)));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons(port());
    CreateSocket();
}

RTypeSocket::RTypeSocket(const std::string &addr) : _socket(), _addr() {
    memset((&_addr), '\0', (sizeof(_addr)));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    _addr.sin_port = htons(port());
    CreateSocket();
}

RTypeSocket::~RTypeSocket() {
    closesocket(_socket);
    WSACleanup();
}

void RTypeSocket::CreateSocket() {
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err < 0) {
        std::cerr << "WSAStartup failed ! " << std::endl;
    }
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket < 0) {
        std::cerr << "Create socket failed ! " << std::endl;
    }
}

void RTypeSocket::Bind() {
    if (bind(_socket, (struct sockaddr *) &_addr, sizeof(_addr))) {
        std::cerr << "Binding port " << port() << " failed !" << std::endl;
    }
    DWORD nonBlocking = 1;
    if (ioctlsocket(_socket, FIONBIO, &nonBlocking) != 0) {
        std::cerr << "Failed to set non-blocking socket !" << std::endl;
    }
}

void RTypeSocket::Receive(RTypeNetworkPayload &payload, size_t length) {
    SOCKADDR_IN  clientAddr;
    int lengthSockAddr = sizeof(clientAddr);

    char *buffer = (char *) malloc(sizeof(char) * length);
    memset((buffer), '\0', (length));
    SSIZE_T data = recvfrom(_socket, buffer, length, 0, (struct sockaddr *) &clientAddr, &lengthSockAddr);
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
