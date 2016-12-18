//
// Created by hippolyteb on 12/18/16.
//

#ifndef R_TYPE_SERVERENTITYPOOL_HPP
#define R_TYPE_SERVERENTITYPOOL_HPP


#include <EntityPool/EntityPool.hpp>

class ServerEntityPool : public EntityPool {
private:
    std::shared_ptr<RType::EventManager> _serverEventManager = nullptr;

public:
    ServerEntityPool(const std::shared_ptr<Timer> &, const std::shared_ptr<RType::EventManager> &);

    virtual ~ServerEntityPool();

public :
    void BroadcastEntities(const std::shared_ptr<RType::EventManager> &eventManager);
};

#endif //R_TYPE_SERVERENTITYPOOL_HPP
