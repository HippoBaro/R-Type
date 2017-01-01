//
// Created by hippolyteb on 12/18/16.
//

#include <Messages/SendNetworkPayloadMessage.hpp>
#include "ServerEntityPool/ServerEntityPool.hpp"

ServerEntityPool::ServerEntityPool(const std::shared_ptr<Timer> &timer, const std::shared_ptr<RType::EventManager> &eventManager) : EntityPool(timer), _serverEventManager(eventManager) { }

void ServerEntityPool::BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager, const std::vector<std::shared_ptr<PlayerRef>> &players) {
    int count = 0;
    for(auto &i : _pool) {
        if (i.second->GetInstance()->getCyclesSinceLastSynch() < 100 && i.second->GetInstance()->getCyclesSinceLastSynch() > 0) {
            i.second->GetInstance()->DidCycleNoSynch();
            continue;
        }
        else
            i.second->GetInstance()->DidSynch();

        auto packer = RType::Packer(RType::WRITE);

        long time = _timer->getCurrent().getMilliseconds().count();
        packer.Pack(time);

        uint16_t type = i.second->GetInstance()->getTypeId();
        packer.Pack(type);
        uint16_t id = i.second->GetInstance()->getId();
        packer.Pack(id);
        i.second->GetInstance()->Serialize(packer);

        for (auto &i : players) {
            eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, i->GetAddress()), this); //todo : send to all clients from the instance
        }

        count++;
    }
    if (count > 0)
        std::cout << "Sent " << count << std::endl;
}

ServerEntityPool::~ServerEntityPool() {

}
