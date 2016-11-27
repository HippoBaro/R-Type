//
// Created by pasteu_e on 26/11/16.
//

#ifndef R_TYPE_RTYPECLIENT_HPP
#define R_TYPE_RTYPECLIENT_HPP


#include <memory>
#include "RTypeNetworkClient.hpp"
#include "SFMLManager.hpp"

class RTypeClient {
private:
    std::unique_ptr<RTypeNetworkClient> _networkClient;
    std::unique_ptr<SFMLManager> _sfmlClient;

public:
    RTypeClient();

    void Run();
};


#endif //R_TYPE_RTYPECLIENT_HPP
