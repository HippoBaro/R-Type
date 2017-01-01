//
// Created by pasteu_e on 27/11/16.
//

#include <Messages/UserInputMessage.hpp>
#include <Entities/Entity.hpp>
#include <Messages/StartReceiveNetworkGamePayload.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <Messages/StopReceiveNetworkGamePayload.hpp>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient(const std::shared_ptr<RType::EventManager> &eventManager,
                                       const std::string &serverIp) : _eventManager(eventManager),
                                                                      _eventListener(eventManager) {

    try {
        _networkClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(serverIp, 6789));
        _currentServerIp = serverIp;
    }
    catch (std::exception ex) {
        std::cerr << "Provided IP adress is malformed, falling back to default : " << _currentServerIp << std::endl;
        _networkClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(_currentServerIp, 6789));
    }


    _networkGameClient->Bind();

    _eventListener.Subscribe<void, StartReceiveNetworkGamePayload>(StartReceiveNetworkGamePayload::EventType, [&](void *, StartReceiveNetworkGamePayload *message) {
        _receiverThread = std::unique_ptr<std::thread>(new std::thread(std::bind(&RTypeNetworkClient::StartReceive, this)));
    });

    _eventListener.Subscribe<void, StopReceiveNetworkGamePayload>(StopReceiveNetworkGamePayload::EventType, [&](void *, StopReceiveNetworkGamePayload *message) {
        StopReceive();
    });

    _eventListener.Subscribe<void, SendNetworkPayloadMessage>(SendNetworkPayloadMessage::EventType, [&](void *, SendNetworkPayloadMessage *message) {
        auto packet = message->ConvertToSocketMessage();
        packet->Ip = _currentServerIp;
        _networkGameUpClient->Send(packet);
    });
}

void RTypeNetworkClient::StartReceive() {
    char data[1500];
    while (!_poisonPill) {
        auto payload = std::make_shared<RTypeNetworkPayload>(data, 1500);
        while (!_poisonPill && _networkGameClient->Receive(payload))
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(payload), this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void RTypeNetworkClient::StopReceive() {
    _poisonPill = true;
    if (_receiverThread != nullptr)
        _receiverThread->join();
}

bool RTypeNetworkClient::TryToConnect() {
    return (_networkClient->Connect());
}

bool RTypeNetworkClient::TryReceive(const int timeout, std::shared_ptr<RTypeNetworkPayload> payload) {
    if (_networkClient->PoolEventOnSocket(DATA_INCOMING, timeout)) {
        _networkClient->Receive(payload);
        return true;
    }
    return false;
}

bool RTypeNetworkClient::TryToSend(const int timeout, std::shared_ptr<RTypeNetworkPayload> payload) {
    if (_networkClient->PoolEventOnSocket(SOMEONE_LISTENING, timeout)) {
        _networkClient->Send(payload);
        return true;
    }
    return false;
}
