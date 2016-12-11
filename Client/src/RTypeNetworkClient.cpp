//
// Created by pasteu_e on 27/11/16.
//

#include <Messages/UserInputMessage.hpp>
#include <Entities/Entity.hpp>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient(std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager), _eventListener(eventManager.get()){
    _eventListener.Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        switch (message->getEventType()) {
            case CLOSE_WINDOWS:
                break;
            case USER_UP:
                break;
            case USER_DOWN:
                break;
            case USER_RIGHT:
                break;
            case USER_LEFT:
                break;
            case USER_SPACE:
                break;
            case USER_ENTER:
                break;
            case USER_ESCAPE:
                break;
            default:
                break;
        }
    });
}