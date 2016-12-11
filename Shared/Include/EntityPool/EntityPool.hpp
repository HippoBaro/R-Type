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
#include <initializer_list>

class EntityPool {
protected:
    std::vector<ManagedExternalInstance<Entity>> _pool = std::vector<ManagedExternalInstance<Entity>>();
    RType::EventManager *_eventManager = new RType::EventManager();
    RType::EventListener _eventListener = RType::EventListener(_eventManager);
    std::shared_ptr<Timer> _timer;

public:
    EntityPool(std::shared_ptr<Timer> const &);

public:
    virtual ~EntityPool();

public:
    virtual void AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &, std::initializer_list<void *> * = nullptr);
    virtual void ProcessEntities();
    void LoadPartition(std::string const &);

public:
    const RType::EventManager *getEventManager() const;

private:
    void SpawnProjectile(FireProjectileMessage const &, const uint16_t emitterId);

private:
    bool GarbageEntities(const ManagedExternalInstance<Entity> &entity);
};


#endif //R_TYPE_ENTITYPOOL_HPP
