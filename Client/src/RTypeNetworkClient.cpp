//
// Created by pasteu_e on 27/11/16.
//

#include <Messages/UserInputMessage.hpp>
#include <Entities/Entity.hpp>
#include <Messages/ReceiveNetworkPayloadMessage.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager), _eventListener(eventManager) {
    _networkGameClient->Bind();

    _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {

    });
    _eventListener.Subscribe<Entity, ReceiveNetworkPayloadMessage>(ReceiveNetworkPayloadMessage::EventType, [&](Entity *, ReceiveNetworkPayloadMessage *message) {
        char data[1500];

        RTypeNetworkPayload payload(data, 1500);
        while (_networkGameClient->Receive(payload)) {
            std::cout << "Received stuff " << _eventManager << std::endl;
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(payload), this);
        }
    });
}