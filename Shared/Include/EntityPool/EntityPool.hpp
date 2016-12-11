//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_ENTITYPOOL_HPP
#define R_TYPE_ENTITYPOOL_HPP

#include <Entities/Entity.hpp>
#include <vector>
#include <memory>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include "EventDispatcher/EventManager.hpp"
#include "EventDispatcher/EventListener.hpp"
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include <Time/Timer.hpp>

class EntityPool {
protected:
    std::vector<ManagedExternalInstance<Entity>> _pool = std::vector<ManagedExternalInstance<Entity>>();
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    RType::EventListener _eventListener = RType::EventListener(_eventManager.get());
    std::shared_ptr<Timer> _timer;

public:
    EntityPool(std::shared_ptr<Timer> const &);

public:
    virtual ~EntityPool();

public:
    virtual void AddEntity(std::string const &entityName, vec2<float> const &initialPos, TimeRef const & = TimeRef());
    virtual void ProcessEntities();
    void LoadPartition(std::string const &);

public:
    const std::shared_ptr<RType::EventManager> &getEventManager() const;

private:
    void SpawnProjectile(FireProjectileMessage const &);

private:
    bool GarbageEntities(const ManagedExternalInstance<Entity> &entity);
};


#endif //R_TYPE_ENTITYPOOL_HPP
