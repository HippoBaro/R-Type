//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPENETWORKCLIENT_HPP
#define R_TYPE_RTYPENETWORKCLIENT_HPP


#include <memory>
#include <thread>
#include <Socket/IRTypeSocket.hpp>
#include <RTypeSocket.hpp>
#include <Socket/Enum/RTypeSocketType.h>
#include <EventDispatcher/EventListener.hpp>

class RTypeNetworkClient {
private:
    std::unique_ptr<IRTypeSocket> _networkClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>("46.101.98.221", 6789));
    std::unique_ptr<IRTypeSocket> _networkGameClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(9876));
    std::unique_ptr<IRTypeSocket> _networkGameUpClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(9875));
    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;
    std::unique_ptr<std::thread> _receiverThread = nullptr;

    bool _poisonPill = false;

public:
    RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager);

private:
    void StartReceive();

public:
    void StopReceive();
    bool TryToConnect();
    bool TryReceive(const int timeout, RTypeNetworkPayload &payload);
    bool TryToSend(const int timeout, const RTypeNetworkPayload &payload);
};


#endif //R_TYPE_RTYPENETWORKCLIENT_HPP
