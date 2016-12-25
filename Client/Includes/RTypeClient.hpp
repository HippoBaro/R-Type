//
// Created by pasteu_e on 26/11/16.
//

#ifndef R_TYPE_RTYPECLIENT_HPP
#define R_TYPE_RTYPECLIENT_HPP

#include <memory>
#include <EventDispatcher/EventManager.hpp>
#include "RTypeNetworkClient.hpp"
#include "SFMLManager.hpp"

class RTypeClient {
private:
    std::shared_ptr<RType::EventManager> _eventManager = std::shared_ptr<RType::EventManager>(new RType::EventManager());
    std::shared_ptr<RTypeNetworkClient> _networkClient = std::unique_ptr<RTypeNetworkClient>(new RTypeNetworkClient(_eventManager));
    std::unique_ptr<SFMLManager> _sfmlManager = std::unique_ptr<SFMLManager>(new SFMLManager(_eventManager, _networkClient));

public:
    void Run();
};


#endif //R_TYPE_RTYPECLIENT_HPP
