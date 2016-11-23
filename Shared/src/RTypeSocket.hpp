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
#define MAX_CLIENTS 100
#define BUF_SIZE 1024

#include <stdlib.h>
#include "IRTypeSocket.hpp"

typedef struct
{
    SOCKADDR_IN sin;
    char name[BUF_SIZE];
}Client;

class RTypeSocket
{

public:
    SOCKET _sock;
    SOCKADDR_IN _sin;
    fd_set _rdfs;
    Client _clients[MAX_CLIENTS];
    char _buffer[BUF_SIZE];
    int _actual;
    int _max;

    RTypeSocket()
    {
        _sin = {0};
        this->_actual = 0;
    }

    virtual void InitConnection()
    {
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sock == INVALID_SOCKET)
        {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        _sin.sin_addr.s_addr = htonl(INADDR_ANY);
        _sin.sin_port = htons(PORT);
        _sin.sin_family = AF_INET;

        std::cout << _sock << std::endl;
        if (bind(_sock, (SOCKADDR *) &_sin, sizeof _sin) == SOCKET_ERROR)
        {
            std::cerr << "bind()" << std::endl;
            throw errno;
        }
        std::cout << "bind ok" << std::endl;
        _max = _sock;
    }


    virtual void InitConnection(const std::string address)
    {
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        struct hostent *hostinfo;

        if(_sock == INVALID_SOCKET)
        {
            std::cerr << "socket()" << std::endl;
            throw errno;
        }

        hostinfo = gethostbyname(address.c_str());
        if (hostinfo == NULL)
        {
            std::cerr << address << std::endl;
            throw errno;
        }

        _sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
        _sin.sin_port = htons(PORT);
        _sin.sin_family = AF_INET;
    }


    virtual bool CheckIfClientExists(Client *clients, SOCKADDR_IN *csin)
    {
        int i = 0;
        for (i = 0; i < _actual; i++)
        {
            if (clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
                && clients[i].sin.sin_port == csin->sin_port) {
                return true;
            }
        }

        return false;
    }

    virtual Client *GetClient(Client *clients, SOCKADDR_IN *csin)
    {
        int i = 0;
        for (i = 0; i < _actual; i++)
        {
            if (clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
                && clients[i].sin.sin_port == csin->sin_port)
            {
                return &clients[i];
            }
        }
        return NULL;
    }

    virtual void RemoveClient(Client *clients, int to_remove)
    {
        memmove(clients + to_remove, clients + to_remove + 1, (_actual - to_remove) * sizeof(Client));
        _actual--;
    }

    virtual void WriteClient(SOCKADDR_IN *sin, const char *buffer)
    {
        if (sendto(_sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0) {
            std::cerr << "send()" << std::endl;
            throw errno;
        }
    }

    virtual void WriteServer(const std::string message)
    {
        if(sendto(_sock, message.c_str(), message.length(), 0, (SOCKADDR *) &_sin, sizeof *&_sin) < 0)
        {
            std::cerr << "can't send message" << std::endl;
            throw errno;
        }
    }


    virtual void SendMessageToAllClients(Client *clients, Client *sender, const char *buffer,
                                         char from_server)
    {
        int i = 0;
        char message[BUF_SIZE];
        message[0] = 0;
        for (i = 0; i < _actual; i++) {
            if (sender != &clients[i]) {
                if (from_server == 0) {
                    strncpy(message, sender->name, BUF_SIZE - 1);
                    strncat(message, " : ", sizeof message - strlen(message) - 1);
                }
                strncat(message, buffer, sizeof message - strlen(message) - 1);
                WriteClient(&clients[i].sin, message);
            }
        }
    }

    virtual void EndConnection()
    {
        closesocket(_sock);
    }

    virtual ssize_t ReadClient(SOCKADDR_IN *sin)
    {
        ssize_t n = 0;
        socklen_t sinsize = sizeof *sin;

        if ((n = recvfrom(_sock, _buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
        {
            std::cerr << "Probleme de reception" << std::endl;
            throw (errno);
        }

        _buffer[n] = 0;

        return n;
    }

    int ReadServer(SOCKADDR_IN *sin)
    {
        int n = 0;
        socklen_t sinsize = sizeof *sin;

        if((n = recvfrom(_sock, _buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize) < 0))
        {
            std::cerr << "Probleme de reception" << std::endl;
            throw (errno);
        }

        _buffer[n] = 0;
        return n;
    }


    virtual void SRun()
    {
        while (1)
        {
            std::cout << "rdfs = " << _rdfs.fds_bits << std::endl;
            FD_ZERO(&_rdfs);
            FD_SET(STDIN_FILENO, &_rdfs);
            FD_SET(_sock, &_rdfs);

            if (select(_max + 1, &_rdfs, NULL, NULL, NULL) == -1)
            {
                std::cerr << "select()" << std::endl;
                throw (errno);
            }
            if (FD_ISSET(STDIN_FILENO, &_rdfs))
            {
                throw (errno);
            } else if (FD_ISSET(_sock, &_rdfs))
            {
                SOCKADDR_IN csin = {0};
                ReadClient(&csin);
                std::cout << "buffer = " << _buffer << " endl"<< std::endl;


                if (CheckIfClientExists(_clients, &csin) == 0)
                {
                    if (_actual != MAX_CLIENTS)
                    {
                        Client c = {csin};
                        strncpy(c.name, _buffer, BUF_SIZE - 1);
                        _clients[_actual] = c;
                        _actual++;
                    }
                } else {
                    Client *client = GetClient(_clients, &csin);

                    if (client != NULL)
                        SendMessageToAllClients(_clients, client, _buffer, 0);
                }
            }
        }
        EndConnection();
    }

    void CRun()
    {
        while(1)
        {
            FD_ZERO(&_rdfs);

            /* add STDIN_FILENO */
            FD_SET(STDIN_FILENO, &_rdfs);

            /* add the socket */
            FD_SET(_sock, &_rdfs);

            if(select(_sock + 1, &_rdfs, NULL, NULL, NULL) == -1)
            {
                perror("select()");
                throw errno;
            }

            /* something from standard input : i.e keyboard */
            if(FD_ISSET(STDIN_FILENO, &_rdfs))
            {
                fgets(_buffer, BUF_SIZE - 1, stdin);
                {
                    char *p = NULL;
                    p = strstr(_buffer, "\n");
                    if(p != NULL)
                    {
                        *p = 0;
                    }
                    else
                    {
                        _buffer[BUF_SIZE - 1] = 0;
                    }
                }
                WriteServer(_buffer);
            }
            else if(FD_ISSET(_sock, &_rdfs))
            {
                int n = ReadServer(&_sin);
                /* server down */
                if(n == 0)
                {
                    std::cout << "Server disconnected !" << std::endl;
                    break;
                }
                std::cout << _buffer << std::endl;
            }
        }
    }


};


#endif //R_TYPE_RTYPESOCKET_HPP
