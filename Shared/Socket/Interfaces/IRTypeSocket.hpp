//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_IRTYPESOCKET_HPP
#define R_TYPE_IRTYPESOCKET_HPP

#include <iostream>

class IRTypeSocket {
public:

    virtual void Bind(const std::string &port) = 0;

    virtual std::string Receive() = 0;

    virtual void Send(const int &socket, const std::string &payload) = 0;

    virtual void Disconnect() = 0;

};

#endif //R_TYPE_IRTYPESOCKET_HPP
