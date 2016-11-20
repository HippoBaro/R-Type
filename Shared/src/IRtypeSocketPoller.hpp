//
// Created by hippolyteb on 11/8/16.
//

#ifndef RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP
#define RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP

#include <vector>
#include "IRtypeSocket.hpp"

class IRtypeSocketPoller {
public:
    virtual std::tuple<std::string, std::string> ReceivePoller(IRtypeSocket *master, std::vector<IRtypeSocket *>) = 0;
};

#endif //RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP
