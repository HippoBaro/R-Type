#ifndef RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP
#define RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP

#include <vector>
#include "IRTypeSocket.hpp"

class IRTypeSocketPoller
{
public:
    virtual std::tuple<std::string, std::string> ReceivePoller(IRTypeSocket *master, std::vector<IRTypeSocket *>) = 0;
};

#endif //RTYPE_SERVER_IRTYPESOCKETPOLLER_HPP
