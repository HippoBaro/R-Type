//
// Created by pasteu_e on 17/12/16.
//

#ifndef R_TYPE_LOBBYMANAGER_HPP
#define R_TYPE_LOBBYMANAGER_HPP

#include <thread>
#include <vector>
#include <LobbyInstance/LobbyInstance.hpp>
#include <NetworkManager/NetworkManager.hpp>

class LobbyManager {
private:
    std::vector<LobbyInstance> _instances = std::vector<LobbyInstance>();
    NetworkManager _networkManager = NetworkManager();

public:
    void Start();
};


#endif //R_TYPE_LOBBYMANAGER_HPP
