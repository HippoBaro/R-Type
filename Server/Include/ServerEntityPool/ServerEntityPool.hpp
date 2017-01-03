//
// Created by hippolyteb on 12/18/16.
//

#ifndef R_TYPE_SERVERENTITYPOOL_HPP
#define R_TYPE_SERVERENTITYPOOL_HPP


#include <EntityPool/EntityPool.hpp>
#include <Entities/PlayerRef.hpp>

class ServerEntityPool : public EntityPool {
private:
    std::shared_ptr<RType::EventManager> _serverEventManager = nullptr;

public:
    ServerEntityPool(const std::shared_ptr<Timer> &, const std::shared_ptr<RType::EventManager> &);

    virtual ~ServerEntityPool();

public :
    void BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager, std::vector<std::shared_ptr<PlayerRef>> &);
    void BroadcastEntitiesThatStillExist(const std::shared_ptr<RType::EventManager> &eventManager, const std::vector<std::shared_ptr<PlayerRef>> &);
};

#endif //R_TYPE_SERVERENTITYPOOL_HPP
