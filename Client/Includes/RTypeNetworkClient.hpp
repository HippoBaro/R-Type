//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPENETWORKCLIENT_HPP
#define R_TYPE_RTYPENETWORKCLIENT_HPP


#include <memory>
#include <Socket/IRTypeSocket.hpp>
#include <RTypeSocket.hpp>
#include <Socket/Enum/RTypeSocketType.h>
#include <EventDispatcher/EventListener.hpp>

class RTypeNetworkClient {
private:
    std::unique_ptr<IRTypeSocket> _networkClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>("127.0.0.1", 8769));
    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;

public:
    RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager);
};


#endif //R_TYPE_RTYPENETWORKCLIENT_HPP
