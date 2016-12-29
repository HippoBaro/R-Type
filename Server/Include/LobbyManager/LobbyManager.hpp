//
// Created by pasteu_e on 17/12/16.
//

#ifndef R_TYPE_LOBBYMANAGER_HPP
#define R_TYPE_LOBBYMANAGER_HPP

#include <thread>
#include <vector>
#include <map>
#include <utility>
#include <LobbyInstance/LobbyInstance.hpp>
#include <NetworkManager/NetworkManager.hpp>
#include <EventDispatcher/EventListener.hpp>
#include <Queue/SingleReaderWriterQueue.hpp>

class LobbyManager {
private:
    uint8_t _nextClientId = 0;
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    NetworkManager _networkManager = NetworkManager(_eventManager);
    std::map<uint8_t, std::shared_ptr<IRTypeSocket>> _clients {};
    std::map<std::string, std::shared_ptr<LobbyInstance>> _instances {};
    std::vector<std::pair<std::shared_ptr<IRTypeSocket>, RTypeNetworkPayload>> _toSend {};

private:
    bool CreateInstance(const std::string &roomName);
    bool JoinInstance(const std::string &roomName, const std::shared_ptr<PlayerRef> &ref);
    void LeftInstance(const std::string &roomName, const uint8_t id);
    void CheckInstance();
    void SendToClients();
    void UserDisconnect(uint8_t id);

public:
    void Start();
    void Run();
};


#endif //R_TYPE_LOBBYMANAGER_HPP
