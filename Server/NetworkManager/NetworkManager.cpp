//
// Created by hippolyteb on 12/12/16.
//

#include <EventDispatcher/EventListener.hpp>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <Messages/ClientWaitForServerMessage.hpp>
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

    _socketDownUDP->Bind();
    char data[1500];
    while (!_poisonPill) {
        auto payload = std::make_shared<RTypeNetworkPayload>(data, 1500);
        while (!_poisonPill && _socketDownUDP->Receive(*payload))
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(payload), this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
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


bool NetworkManager::SendOverTCP(RTypeNetworkPayload const &payload, std::shared_ptr<IRTypeSocket> &client, int timeout) {
    if (client->PoolEventOnSocket(SOMEONE_LISTENING, timeout)) {
        client->Send(payload);
        return true;
    }
    return false;
}

void NetworkManager::CheckForIncomingMessage(std::map<uint8_t, std::shared_ptr<IRTypeSocket>> &clients) {
    char data[1500];
    auto payload = std::make_shared<RTypeNetworkPayload>(data, 1500);
    for (auto it = clients.cbegin(); it != clients.cend();) {
        if ((*it->second).PoolEventOnSocket(SOCKET_CLOSED, 0)) {
            auto clientMessage = new ClientWaitForServerMessage(USER_DISCONNECT);
            RType::Packer packer(RType::WRITE);
            clientMessage->Serialize(packer);
            payload->Payload = packer.getBuffer();
            payload->Length = packer.getLength();
            _eventManager->Emit(ReceivedTCPNetworkPayloadMessage::EventType, new ReceivedTCPNetworkPayloadMessage(it->first, payload), this);
            break;
        } else if ((*it->second).PoolEventOnSocket(DATA_INCOMING, 0)) {
            (*it->second).Receive(*payload);
            _eventManager->Emit(ReceivedTCPNetworkPayloadMessage::EventType, new ReceivedTCPNetworkPayloadMessage(it->first, payload), this);
            break;
        } else {
            ++it;
        }
    }
}