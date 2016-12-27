//
// Created by hippolyteb on 12/12/16.
//

#include <EventDispatcher/EventListener.hpp>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "NetworkManager/NetworkManager.hpp"

void NetworkManager::Start() {
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&NetworkManager::Run, this)));
}

void NetworkManager::Run() {
    auto sub = RType::EventListener(_eventManager);

    sub.Subscribe<void, SendNetworkPayloadMessage>(SendNetworkPayloadMessage::EventType, [&](void *sender, SendNetworkPayloadMessage *message) {
        Send(message->ConvertToSocketMessage());
    });

    _socketDownUDP->Bind();
    char data[1500];
    while (!_poisonPill) {
        auto payload = std::make_shared<RTypeNetworkPayload>(data, 1500);
        while (!_poisonPill && _socketDownUDP->Receive(*payload))
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(payload), this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

NetworkManager::NetworkManager(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(
        eventManager) {}

void NetworkManager::Send(RTypeNetworkPayload const &payload) {
    if (_clients.find(payload.Ip) == _clients.end() ) {
        _clients[payload.Ip] = std::unique_ptr<RTypeSocket<UDP>>(new RTypeSocket<UDP>(payload.Ip, 9876));
    } else {
        _clients[payload.Ip]->Send(payload);
    }
}