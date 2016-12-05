//
// Created by barre_k on 30/11/16.
//

#include "RTypeSocket.hpp"

RTypeSocket::RTypeSocket() : IRTypeSocket()
{
    _payload = new Payload();
    _temppayload = new Payload();
}

RTypeSocket::~RTypeSocket() {
#ifdef _WIN32
    WSACleanup();
#endif
    closesocket(_payload->_sock);
    delete _payload;
    delete _temppayload;
}

void RTypeSocket::InitConnection(uint16_t port) {
#ifdef _WIN32
    WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      throw new std::runtime_error("socket error on init connection");
   }
#endif
    _payload->_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (_payload->_sock == INVALID_SOCKET) {
        throw std::runtime_error("socket error on init connection");
    }

    _payload->_type = SERVER;
    _payload->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    _payload->_sin.sin_port = htons(port);
    _payload->_sin.sin_family = AF_INET;

    if (bind(_payload->_sock, (SOCKADDR *) &_payload->_sin, sizeof _payload->_sin) == SOCKET_ERROR) {
        throw std::runtime_error("bind error on init connection");
    }
}

void RTypeSocket::InitConnection(const std::string address, uint16_t port) {
#ifdef _WIN32
    WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      throw new std::runtime_error("socket error on init connection");
   }
#endif
    _payload->_sock = socket(AF_INET, SOCK_DGRAM, 0);
    std::cout << "clients socket" << _payload->_sock << std::endl;
    struct hostent *hostinfo;

    if (_payload->_sock == INVALID_SOCKET) {
        throw std::runtime_error("socket error on init connection");
    }

    hostinfo = gethostbyname(address.c_str());
    if (hostinfo == NULL) {
        throw std::runtime_error("error when get hostname on init connection");
    }
    _payload->_type = CLIENT;
    _payload->_sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    _payload->_sin.sin_port = htons(port);
    _payload->_sin.sin_family = AF_INET;
}


void RTypeSocket::Send(const Payload *payload, const char *message) {
    if (sendto(_payload->_sock, message, MTU - 1, 0, (SOCKADDR *) &payload->_sin, sizeof payload->_sin) < 0) {
        throw std::runtime_error("cant send message");
    }
}

void RTypeSocket::Send(const char *message) {
    if (sendto(_payload->_sock, message, MTU - 1, 0, (SOCKADDR *) &_payload->_sin, sizeof *&_payload->_sin) < 0) {
        throw std::runtime_error("cant send message");
    }
}

Payload *RTypeSocket::GetNativePayload() {
    return this->_payload;
}

Payload *RTypeSocket::Receive() {
    FD_ZERO(&_payload->_rdfs);
    FD_SET(STDIN_FILENO, &_payload->_rdfs);
    FD_SET(_payload->_sock, &_payload->_rdfs);

    if (select(_payload->_sock + 1, &_payload->_rdfs, NULL, NULL, NULL) == -1) {
        throw std::runtime_error("cant receive message select error");
    }


    if (FD_ISSET(_payload->_sock, &_payload->_rdfs)) {

        if (_payload->_type == CLIENT) {
            socklen_t sinsize = sizeof *(&_payload->_sin);
            if (recvfrom(_payload->_sock, _payload->_buffer, MTU - 1, 0, (SOCKADDR *) &_payload->_sin, &sinsize) < 0) {
                throw std::runtime_error("cant receive message");
            }
            return _payload;
        } else if (_payload->_type == SERVER) {
            SOCKADDR_IN csin;
            memset(&csin, 0, sizeof(SOCKADDR_IN));
            socklen_t sinsize = sizeof *&csin;

            if (recvfrom(_payload->_sock, _temppayload->_buffer, MTU - 1, 0, (SOCKADDR *) &csin, &sinsize) < 0) {
                throw std::runtime_error("reception error");
            }
            _temppayload->_sock = _payload->_sock;
            _temppayload->_sin = csin;
            return _temppayload;
        }

    }
    return nullptr;
}