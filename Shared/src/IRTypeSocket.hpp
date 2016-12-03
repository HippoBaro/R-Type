#ifndef RTYPE_SERVER_IRTYPESOCKET_HPP
#define RTYPE_SERVER_IRTYPESOCKET_HPP

#include <string>
#include <iostream>
#include <sstream>

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

#define MTU 1500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
/* Structure describing a generic socket address.  */
typedef struct sockaddr SOCKADDR;
/* Internet address. struct descriptor  */
typedef struct in_addr IN_ADDR;

enum type
{
    SERVER,
    CLIENT
};

class Payload
{
public:
    /* fd_set for select and pselect.  */
    fd_set _rdfs;
    //    fd du socket
    SOCKET _sock;
    /* Structure describing an Internet socket address.  */
    SOCKADDR_IN _sin;
    enum type _type;
    char _buffer[MTU];

    ~Payload() {}
    Payload() {
        _sin = {0};
    }
};

class IRTypeSocket {

public:
    IRTypeSocket() {}

    virtual ~IRTypeSocket() {}

    virtual void Send(const char *message) = 0;
    virtual void Send(const Payload *payload, const char *message) = 0;

    virtual void InitConnection(uint16_t port) = 0;

    virtual void InitConnection(const std::string address, uint16_t port) = 0;

    virtual Payload* GetNativePayload() = 0;

    virtual Payload *Receive() = 0;
};

#endif //RTYPE_SERVER_IRTYPESOCKET_HPP
