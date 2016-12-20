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
    void RunTCP();
    void Send(RTypeNetworkPayload const &payload);
    void SendTCP(RTypeNetworkPayload const &payload, std::unique_ptr<IRTypeSocket> &_client);
    void ThreadAskingRoomName(std::shared_ptr<IRTypeSocket> client);

public:
    void Start();
    void StartTCP();
    void AskClientForRoomName(std::shared_ptr<IRTypeSocket> client);
};


#endif //R_TYPE_NETWORKMANAGER_HPP
