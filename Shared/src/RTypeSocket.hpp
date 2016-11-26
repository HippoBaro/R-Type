//
// Created by barre_k on 20/11/16.
//

#ifndef R_TYPE_RTYPESOCKET_HPP
#define R_TYPE_RTYPESOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define PORT 1977
#define MAX_CLIENTS 10
#define BUF_SIZE 1500

#include <stdlib.h>
#include "IRTypeSocket.hpp"

typedef struct {
    SOCKADDR_IN sin;
}   Client;

class RTypeSocket {

private:
    SOCKET _sock;
    SOCKADDR_IN _sin;
    fd_set _rdfs;
    Client _clients[MAX_CLIENTS];
    Client *_actual_client;
    char _buffer[BUF_SIZE];
    int _actual;
    int _max;

public:
    RTypeSocket()
    {
        _sin = {0};
        _actual = 0;
    }

    virtual void InitConnection() {
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sock == INVALID_SOCKET) {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        _sin.sin_addr.s_addr = htonl(INADDR_ANY);
        _sin.sin_port = htons(PORT);
        _sin.sin_family = AF_INET;

        if (bind(_sock, (SOCKADDR *) &_sin, sizeof _sin) == SOCKET_ERROR) {
            std::cerr << "bind()" << std::endl;
            throw errno;
        }
        _max = _sock;
    }


    virtual void InitConnection(const std::string address) {
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        struct hostent *hostinfo;

        if (_sock == INVALID_SOCKET) {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        hostinfo = gethostbyname(address.c_str());
        if (hostinfo == NULL) {
            std::cerr << address << std::endl;
            throw errno;
        }

        _sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
        _sin.sin_port = htons(PORT);
        _sin.sin_family = AF_INET;
    }


    virtual bool CheckIfClientExists(SOCKADDR_IN *csin) {
        int i = 0;
        for (i = 0; i < _actual; i++) {
            if (_clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
                && _clients[i].sin.sin_port == csin->sin_port) {
                return true;
            }
        }

        return false;
    }

    virtual Client *GetClient(SOCKADDR_IN *csin) {
        for (int i = 0; i < _actual; i++) {
            if (_clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
                && _clients[i].sin.sin_port == csin->sin_port) {
                return &_clients[i];
            }
        }
        return NULL;
    }

    virtual void RemoveClient(int to_remove) {
        memmove(_clients + to_remove, _clients + to_remove + 1, (_actual - to_remove) * sizeof(Client));
        _actual--;
    }

    virtual void WriteClient(SOCKADDR_IN *sin, const char *buffer) {
        if (sendto(_sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0) {
            std::cerr << "send()" << std::endl;
            throw errno;
        }
    }

    virtual void WriteServer(const char* message) {
        if (sendto(_sock, message, BUF_SIZE - 1, 0, (SOCKADDR *) &_sin, sizeof *&_sin) < 0) {
            std::cerr << "can't send message" << std::endl;
            throw errno;
        }
    }


    virtual void SendMessageToAllClients(const char *message)
    {
        for (int i = 0; i < _actual; i++)
        {
//            if (_actual_client != &_clients[i])
//            {
//            }
            WriteClient(&_clients[i].sin, message);
        }
    }

    virtual void EndConnection() {
        closesocket(_sock);
    }

    virtual ssize_t ReadClient(SOCKADDR_IN *sin)
    {
        ssize_t n = 0;
        socklen_t sinsize = sizeof *sin;

        if ((n = recvfrom(_sock, _buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0) {
            std::cerr << "Probleme de reception" << std::endl;
            throw (errno);
        }
        _buffer[n] = 0;
        return n;
    }

    int ReadServer() {
        int n = 0;
        socklen_t sinsize = sizeof *(&_sin);

        if((n = recvfrom(_sock, _buffer, BUF_SIZE - 1, 0, (SOCKADDR *) &_sin, &sinsize)) < 0)
        {
            throw errno;
        }

        _buffer[n] = 0;
        return n;

    }


    char* ListenClient()
    {
        FD_ZERO(&_rdfs);
        FD_SET(STDIN_FILENO, &_rdfs);
        FD_SET(_sock, &_rdfs);
        if (select(_max + 1, &_rdfs, NULL, NULL, NULL) == -1) {
            std::cerr << "select()" << std::endl;
            throw (errno);
        }
        if (FD_ISSET(STDIN_FILENO, &_rdfs))
        {
            EndConnection();
            std::cerr << "key press is not compatiblex" << std::endl;
            throw (errno);
        }
        else if (FD_ISSET(_sock, &_rdfs))
        {
            SOCKADDR_IN csin = {0};
            ReadClient(&csin);

            if (CheckIfClientExists(&csin) == 0) {
                if (_actual != MAX_CLIENTS)
                {
                    Client c = {csin};
                    _clients[_actual] = c;
                    _actual++;
                    return _buffer;
                }
            }
            else
            {
                _actual_client = GetClient(&csin);
                if (_actual_client != NULL)
                    return _buffer;
                else
                    return nullptr;
            }
        }
        return nullptr;
    }

    char* ListenServer()
    {
        FD_ZERO(&_rdfs);
        FD_SET(STDIN_FILENO, &_rdfs);
        FD_SET(_sock, &_rdfs);

        if (select(_sock + 1, &_rdfs, NULL, NULL, NULL) == -1)
        {
            std::cerr << "select error" << std::endl;
            throw errno;
        }
        if (FD_ISSET(_sock, &_rdfs))
        {
            ReadServer();
            return _buffer;
        }
        return nullptr;
    }

};


#endif //R_TYPE_RTYPESOCKET_HPP
