//
// Created by hippolyteb on 12/12/16.
//

#ifndef R_TYPE_NETWORKMANAGER_HPP
#define R_TYPE_NETWORKMANAGER_HPP


#include <thread>
#include <Socket/RTypeSocket.hpp>
#include <EventDispatcher/EventManager.hpp>

class NetworkManager {
private:
    std::unique_ptr<std::thread> _thread = nullptr;
    std::unique_ptr<IRTypeSocket> _socketUDP = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(9876));
    std::shared_ptr<RType::EventManager> _eventManager = nullptr;
    std::map<std::string, std::unique_ptr<RTypeSocket<UDP>>> _clients = std::map<std::string, std::unique_ptr<RTypeSocket<UDP>>>();

public:
    NetworkManager(const std::shared_ptr<RType::EventManager> &eventManager);

private:
    void Run();
    void Send(RTypeNetworkPayload const &payload);

public:
    void Start();
};


#endif //R_TYPE_NETWORKMANAGER_HPP
