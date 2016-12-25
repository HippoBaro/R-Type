//
// Created by pasteu_e on 27/11/16.
//

#include <Messages/UserInputMessage.hpp>
#include <Entities/Entity.hpp>
#include <Messages/StartReceiveNetworkGamePayload.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <Messages/StopReceiveNetworkGamePayload.hpp>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager), _eventListener(eventManager) {
    _networkGameClient->Bind();

    _eventListener.Subscribe<Entity, StartReceiveNetworkGamePayload>(StartReceiveNetworkGamePayload::EventType, [&](Entity *, StartReceiveNetworkGamePayload *message) {
        _receiverThread = std::unique_ptr<std::thread>(new std::thread(std::bind(&RTypeNetworkClient::StartReceive, this)));
    });

    _eventListener.Subscribe<Entity, StopReceiveNetworkGamePayload>(StopReceiveNetworkGamePayload::EventType, [&](Entity *, StopReceiveNetworkGamePayload *message) {
        StopReceive();
    });
}

void RTypeNetworkClient::StartReceive() {
    char data[1500];
    while (!_poisonPill) {
        auto payload = std::make_shared<RTypeNetworkPayload>(data, 1500);
        while (!_poisonPill && _networkGameClient->Receive(*payload))
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(payload), this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void RTypeNetworkClient::StopReceive() {
    _poisonPill = true;
    _receiverThread->join();
}

bool RTypeNetworkClient::TryToConnect() {
    return (_networkClient->Connect());
}

bool RTypeNetworkClient::TrytoReceive(int timeout, RTypeNetworkPayload &payload) {
    if (_networkClient->PoolEventOnSocket(DATA_INCOMING, timeout)) {
        _networkClient->Receive(payload);
        return true;
    }
    return false;
}

bool RTypeNetworkClient::TryToSend(int timeout, RTypeNetworkPayload &payload) {
    if (_networkClient->PoolEventOnSocket(SOMEONE_LISTENING, timeout)) {
        _networkClient->Send(payload);
        return true;
    }
    return false;
}
