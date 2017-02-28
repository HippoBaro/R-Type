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
#include <EntityFactory/EntityFactory.hpp>

class EntityPool {
protected:
    std::map<uint16_t, std::shared_ptr<ManagedExternalInstance<Entity>>> _pool = std::map<uint16_t, std::shared_ptr<ManagedExternalInstance<Entity>>> ();
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    RType::EventListener _eventListener = RType::EventListener(_eventManager);
    std::shared_ptr<Timer> _timer;
    EntityFactory _factory = EntityFactory();

public:
    EntityPool(std::shared_ptr<Timer> const &);

public:
    virtual ~EntityPool();

public:
    virtual void AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &, std::initializer_list<void *> * = nullptr);
    virtual void AddEntity(const std::shared_ptr<ManagedExternalInstance<Entity>> &);
    virtual void ProcessEntities();
    virtual void LoadPartition(std::string const &);
    virtual void RegisterType(std::string const &);
    bool Exist(const uint16_t);
    bool isPlayer(const uint16_t);
    uint16_t getEntityCount();
    virtual std::shared_ptr<ManagedExternalInstance<Entity>> &getEntityById(uint16_t);

public:
    std::shared_ptr<RType::EventManager> &getEventManager();

protected:
    virtual void SpawnProjectile(FireProjectileMessage const &);

private:
    bool GarbageEntities(const ManagedExternalInstance<Entity> &entity);

public:
    EntityFactory &getFactory();
};


#endif //R_TYPE_ENTITYPOOL_HPP
