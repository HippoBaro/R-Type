//
// Created by pasteu_e on 27/11/16.
//

#include <Messages/UserInputMessage.hpp>
#include <Entities/Entity.hpp>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager), _eventListener(eventManager) {
    _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {

    });
}