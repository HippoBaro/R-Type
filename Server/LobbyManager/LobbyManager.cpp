//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"

void LobbyManager::Start() {
    auto sub = RType::EventListener(_eventManager);
    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        _clients[_i++] = message->getClient();
    });
    Run();
}

void LobbyManager::Run() {
    std::shared_ptr<IRTypeSocket> tmp;
    while (true) {
        _networkManager.IsThereNewClient();
        _networkManager.CheckForIncomingMessage(_clients);
        std::cout << _clients.size() << std::endl;
    }
}

LobbyManager::LobbyManager() : _clients() {

}
