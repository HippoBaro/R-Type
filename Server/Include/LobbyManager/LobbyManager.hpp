//
// Created by pasteu_e on 17/12/16.
//

#ifndef R_TYPE_LOBBYMANAGER_HPP
#define R_TYPE_LOBBYMANAGER_HPP

#include <thread>
#include <vector>
#include <LobbyInstance/LobbyInstance.hpp>
#include <NetworkManager/NetworkManager.hpp>
#include <EventDispatcher/EventListener.hpp>
#include <Queue/SingleReaderWriterQueue.hpp>

class LobbyManager {
private:
    uint8_t _i = 0;
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    NetworkManager _networkManager = NetworkManager(_eventManager);
    std::map<uint8_t, std::shared_ptr<IRTypeSocket>> _clients = std::map<uint8_t, std::shared_ptr<IRTypeSocket>>();
    std::map<std::string, std::shared_ptr<LobbyInstance>> _instances = std::map<std::string, std::shared_ptr<LobbyInstance>>();

private:
    bool CreateInstance(std::string &roomName);
    bool JoinInstance(std::string &roomName, std::shared_ptr<PlayerRef> &ref);
    void LeftInstance(std::string &roomName, uint8_t id);
    void CheckInstance();
    void NotifyClients();
public:
    void Start();
    void Run();
};


#endif //R_TYPE_LOBBYMANAGER_HPP
