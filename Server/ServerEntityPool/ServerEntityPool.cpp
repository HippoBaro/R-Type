//
// Created by hippolyteb on 12/18/16.
//

#include <Messages/SendNetworkPayloadMessage.hpp>
#include "ServerEntityPool/ServerEntityPool.hpp"

ServerEntityPool::ServerEntityPool(const std::shared_ptr<Timer> &timer, const std::shared_ptr<RType::EventManager> &eventManager) : EntityPool(timer), _serverEventManager(eventManager) { }

void ServerEntityPool::BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager) {
    for(auto &i : _pool) {
        auto packer = RType::Packer(RType::WRITE);
        i->Serialize(packer);
        eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, "127.0.0.1"), this); //todo : send to all clients from the instance
    }
}

ServerEntityPool::~ServerEntityPool() {

}
