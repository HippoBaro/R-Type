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
    std::unique_ptr<IRTypeSocket> _socketDownUDP = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(9875));
    std::unique_ptr<IRTypeSocket> _socketTCP = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(6789));
    std::shared_ptr<RType::EventManager> _eventManager = nullptr;
    std::map<std::string, std::unique_ptr<RTypeSocket<UDP>>> _clients = std::map<std::string, std::unique_ptr<RTypeSocket<UDP>>>();
    bool _poisonPill = false;

private:
    void Run();
    void Send(std::shared_ptr<RTypeNetworkPayload> payload);

public:
    NetworkManager(const std::shared_ptr<RType::EventManager> &eventManager);
    bool SendOverTCP(std::shared_ptr<RTypeNetworkPayload> payload, std::shared_ptr<IRTypeSocket> &client, int timeout);
    void Start();
    void IsThereNewClient();
    void CheckForIncomingMessage(std::map<uint8_t, std::shared_ptr<IRTypeSocket>> &);
};


#endif //R_TYPE_NETWORKMANAGER_HPP
