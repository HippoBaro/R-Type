//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"

void LobbyManager::Start() {
    _networkManager.StartTCP();

    auto sub = RType::EventListener(_eventManager);
    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        _clients.enqueue(message->getClient());
    });
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&LobbyManager::Run, this)));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
}

void LobbyManager::Run() {
    std::shared_ptr<IRTypeSocket> tmp;
    while (true) {
        while (!_clients.try_dequeue(tmp));
        _networkManager.AskClientForRoomName(tmp);
        _clientsContacted.enqueue(tmp);
    }
}

LobbyManager::LobbyManager() : _clients(), _clientsContacted() {

}
