//
// Created by aguado_e on 11/21/16.
//

#include <EventDispatcher/EventManager.hpp>

RType::EventManager::EventManager() {}

void RType::EventManager::AddListener(std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(Entity&, IMessage *message)>>>> &callbacks) {
    _listeners.push_back(callbacks);
}

void RType::EventManager::Emit(RType::Event event, IMessage *message, Entity &sender) {
    for (auto const callbacklist : _listeners) {
        if (callbacklist != nullptr)
            for (auto callback : (*callbacklist)[event])
                callback(sender, message);
    }
    if (message)
        delete message;
}
