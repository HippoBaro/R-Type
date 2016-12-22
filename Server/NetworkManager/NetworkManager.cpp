//
// Created by hippolyteb on 12/12/16.
//

#include <EventDispatcher/EventListener.hpp>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/SendTCPNetworkPayloadMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include "NetworkManager/NetworkManager.hpp"

NetworkManager::NetworkManager(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager) {
    _socketTCP->Bind();
}

void NetworkManager::Start() {
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&NetworkManager::Run, this)));
}

void NetworkManager::Run() {

    auto sub = RType::EventListener(_eventManager);

    sub.Subscribe<void, SendNetworkPayloadMessage>(SendNetworkPayloadMessage::EventType, [&](void *sender, SendNetworkPayloadMessage *message) {
        Send(message->ConvertToSocketMessage());
    });

    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void NetworkManager::Send(RTypeNetworkPayload const &payload) {
    if (_clients.find(payload.Ip) == _clients.end()) {
        _clients[payload.Ip] = std::unique_ptr<RTypeSocket<UDP>>(new RTypeSocket<UDP>(payload.Ip, 9876));
    } else {
        _clients[payload.Ip]->Send(payload);
    }
}


void NetworkManager::IsThereNewClient() {
    if (_socketTCP->PoolEventOnSocket(DATA_INCOMING, 500)) {
        std::shared_ptr<IRTypeSocket> newClient = _socketTCP->Accept();
        if (newClient != nullptr) {
            _eventManager->Emit(NewClientConnectionMessage::EventType, new NewClientConnectionMessage(newClient), this);
        }
    }
}


void NetworkManager::SendOverTCP(RTypeNetworkPayload const &payload, std::unique_ptr<IRTypeSocket> &_client) {

}

void NetworkManager::CheckForIncomingMessage(std::map<uint8_t, std::shared_ptr<IRTypeSocket>> &clients) {
    char data[1500];

    RTypeNetworkPayload payload(data, 1500);
    for (auto it = clients.cbegin(); it != clients.cend();) {
        if ((*it->second).PoolEventOnSocket(SOCKET_CLOSED, 0)) {
            clients.erase(it++);
        } else if ((*it->second).PoolEventOnSocket(DATA_INCOMING, 0)) {
            (*it->second).Receive(payload);
            ++it;
        } else {
            ++it;
        }
    }
}