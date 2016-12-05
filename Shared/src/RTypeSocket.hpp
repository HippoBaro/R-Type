//
// Created by barre_k on 30/11/16.
//

#ifndef R_TYPE_RTYPESOCKET_HPP
#define R_TYPE_RTYPESOCKET_HPP

#include "IRTypeSocket.hpp"

class RTypeSocket : public IRTypeSocket
{
private:
    Payload *_payload;
    Payload *_temppayload;

public:

    RTypeSocket() : IRTypeSocket()
    {
        _payload = new Payload();
        _temppayload = new Payload();
    }

    virtual ~RTypeSocket() {
        closesocket(_payload->_sock);
        delete _payload;
        delete _temppayload;
    }

    virtual void InitConnection(uint16_t port)
    {
        _payload->_sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (_payload->_sock == INVALID_SOCKET) {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        _payload->_type = SERVER;
        _payload->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
        _payload->_sin.sin_port = htons(port);
        _payload->_sin.sin_family = AF_INET;

        if (bind(_payload->_sock, (SOCKADDR *) &_payload->_sin, sizeof _payload->_sin) == SOCKET_ERROR) {
            std::cerr << "bind()" << std::endl;
            throw errno;
        }
    }

//  set server connection to server
    void InitConnection(const std::string address, uint16_t port)
    {
        _payload->_sock = socket(AF_INET, SOCK_DGRAM, 0);
        std::cout << "clients socket" << _payload->_sock << std::endl;
        struct hostent *hostinfo;

        if (_payload->_sock == INVALID_SOCKET) {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        hostinfo = gethostbyname(address.c_str());
        if (hostinfo == NULL) {
            std::cerr << address << " error" << std::endl;
            throw errno;
        }
        _payload->_type = CLIENT;
        _payload->_sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
        _payload->_sin.sin_port = htons(port);
        _payload->_sin.sin_family = AF_INET;
    }

    virtual Payload *Receive()
    {
        FD_ZERO(&_payload->_rdfs);
        FD_SET(STDIN_FILENO, &_payload->_rdfs);
        FD_SET(_payload->_sock, &_payload->_rdfs);

        if (select(_payload->_sock + 1, &_payload->_rdfs, NULL, NULL, NULL) == -1) {
            std::cerr << "select errors" << std::endl;
            return nullptr;
        }



        if (FD_ISSET(_payload->_sock, &_payload->_rdfs))
        {

            if (_payload->_type == CLIENT)
            {
                std::cout << "i am client i recieve from server" << std::endl;
                socklen_t sinsize = sizeof *(&_payload->_sin);
                if (recvfrom(_payload->_sock, _payload->_buffer, MTU - 1, 0, (SOCKADDR *) &_payload->_sin, &sinsize) < 0) {
                    throw errno;
                }
                return _payload;
            }
            else if (_payload->_type == SERVER)
            {
                std::cout << "i am server i recieve from client" << std::endl;
                SOCKADDR_IN csin = {0};
                socklen_t sinsize = sizeof *&csin;

                if (recvfrom(_payload->_sock, _temppayload->_buffer, MTU - 1, 0, (SOCKADDR *) &csin, &sinsize) < 0)
                {
                    std::cerr << "Probleme de reception" << std::endl;
                    throw (errno);
                }
                _temppayload->_sock = _payload->_sock;
                _temppayload->_sin = csin;
                return _temppayload;
            }

        }
        return nullptr;
    }

    virtual Payload *GetNativePayload() {
        return this->_payload;
    }

    virtual void Send(const Payload *payload, const char *message) {
        if (sendto(_payload->_sock, message, MTU - 1, 0, (SOCKADDR *) &payload->_sin, sizeof payload->_sin) < 0) {
            std::cerr << "can't send message" << std::endl;
            throw errno;
        }
    }
    virtual void Send(const char *message) {
        if (sendto(_payload->_sock, message, MTU - 1, 0, (SOCKADDR *) &_payload->_sin, sizeof *&_payload->_sin) < 0) {
            std::cerr << "can't send message" << std::endl;
            throw errno;
        }
    }
};


#endif //R_TYPE_RTYPESOCKET_HPP
