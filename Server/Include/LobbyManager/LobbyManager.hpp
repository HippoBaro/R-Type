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
    std::unique_ptr<std::thread> _thread = nullptr;
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    NetworkManager _networkManager = NetworkManager(_eventManager);
    std::vector<std::shared_ptr<IRTypeSocket>> _clients;
    std::map<std::string, LobbyInstance> _instances = std::map<std::string, LobbyInstance>();

public:
    LobbyManager();
    void Start();
    void Run();
};


#endif //R_TYPE_LOBBYMANAGER_HPP
