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
        std::vector<std::shared_ptr<RTypeNetworkPayload>> payloads;

        auto payload = std::make_shared<RTypeNetworkPayload>(1500);
        while (_networkGameClient->Receive(*payload)) {
            payloads.push_back(payload);
            payload = std::make_shared<RTypeNetworkPayload>(1500);
        }

        uint8_t i;
        if (payloads.size() < 10)
            i = 0;
        else
            i = static_cast<uint8_t>(payloads.size() - 10);

        while (i < payloads.size()) {
            std::cout << "Received stuff " << _eventManager << std::endl;
            _eventManager->Emit(ReceivedNetworkPayloadMessage::EventType, new ReceivedNetworkPayloadMessage(*payloads[i]), this);
            i++;
        }

        std::cout << "Drawing" << std::endl;
    });
}