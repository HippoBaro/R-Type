//
// Created by hippolyteb on 12/18/16.
//

#include <Messages/SendNetworkPayloadMessage.hpp>
#include "ServerEntityPool/ServerEntityPool.hpp"

ServerEntityPool::ServerEntityPool(const std::shared_ptr<Timer> &timer,
                                   const std::shared_ptr<RType::EventManager> &eventManager) :
        EntityPool(timer),
        _serverEventManager(eventManager) { }

void ServerEntityPool::BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager,
                                         const std::vector<std::shared_ptr<PlayerRef>> &players) {
    int count = 0;
    for(auto &i : _pool) {
        if (i.second->GetInstance()->getCyclesSinceLastSynch() < 100 && i.second->GetInstance()->getCyclesSinceLastSynch() > 0) {
            i.second->GetInstance()->DidCycleNoSynch();
            continue;
        }
        else
            i.second->GetInstance()->DidSynch();

        auto packer = RType::Packer(RType::WRITE);

        uint8_t typeP = 1;
        packer.Pack(typeP);

        uint64_t time = (uint64_t) _timer->getCurrent().getMilliseconds().count();
        packer.Pack(time);

        uint16_t type = i.second->GetInstance()->getTypeId();
        packer.Pack(type);
        uint16_t id = i.second->GetInstance()->getId();
        packer.Pack(id);
        i.second->GetInstance()->Serialize(packer);

        for (auto &i : players) {
            eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, i->GetAddress()), this);
        }

        count++;
    }
    if (count > 0)
        std::cout << "Sent " << count << std::endl;
}

ServerEntityPool::~ServerEntityPool() {

}

void ServerEntityPool::BroadcastEntitiesThatStillExist(const std::shared_ptr<RType::EventManager> &eventManager,
                                                       const std::vector<std::shared_ptr<PlayerRef>> &players) {
    auto packer = RType::Packer(RType::WRITE);

    //uint64_t time = (uint64_t) _timer->getCurrent().getMilliseconds().count();
    //packer.Pack(time);

    uint8_t type = 0;
    packer.Pack(type);

    std::set<std::uint16_t> entities;

    for(auto &i : _pool) {
        entities.insert(i.first);
    }
    packer.Pack(entities);
    for (auto &i : players) {
        eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, i->GetAddress()), this);
    }
}
