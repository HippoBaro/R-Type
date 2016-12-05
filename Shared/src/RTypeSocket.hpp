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

    RTypeSocket();

    virtual ~RTypeSocket();

    virtual void InitConnection(uint16_t port);

//  set server connection to server
    void InitConnection(const std::string address, uint16_t port);

    virtual Payload *Receive();

    virtual Payload *GetNativePayload();

    virtual void Send(const Payload *payload, const char *message);

    virtual void Send(const char *message);
};


#endif //R_TYPE_RTYPESOCKET_HPP
