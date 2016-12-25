//
// Created by hippolyteb on 12/18/16.
//

#include <Messages/SendNetworkPayloadMessage.hpp>
#include "ServerEntityPool/ServerEntityPool.hpp"

ServerEntityPool::ServerEntityPool(const std::shared_ptr<Timer> &timer, const std::shared_ptr<RType::EventManager> &eventManager) : EntityPool(timer), _serverEventManager(eventManager) { }

void ServerEntityPool::BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager) {
    int count = 0;
    for(auto &i : _pool) {
        if (i.second->getCyclesSinceLastSynch() < 100 && i.second->getCyclesSinceLastSynch() > 0) {
            i.second->DidCycleNoSynch();
            continue;
        }
        else
            i.second->DidSynch();

        auto packer = RType::Packer(RType::WRITE);

        long time = _timer->getCurrent().getMilliseconds().count();
        packer.Pack(time);

        uint16_t type = i.second->getTypeId();
        packer.Pack(type);
        uint16_t id = i.second->getId();
        packer.Pack(id);
        i.second->Serialize(packer);
        eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, "127.0.0.1"), this); //todo : send to all clients from the instance
        count++;
    }
    if (count > 0)
        std::cout << "Sent " << count << std::endl;
}

ServerEntityPool::~ServerEntityPool() {

}
