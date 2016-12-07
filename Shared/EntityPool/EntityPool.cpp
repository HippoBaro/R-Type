//
// Created by hippolyteb on 11/28/16.
//

#include <Entities/DrawableEntity.hpp>
#include <EntityPool/EntityPool.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include <iostream>

void EntityPool::AddEntity(std::string const &entityName, vec2<float> const &initialPos) {
    auto now = _timer->getCurrent();
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, {_timer.get() , _eventManager.get(), &now, &pos }, "create", "destroy"));
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool(std::shared_ptr<Timer> const &timer) : _timer(timer) {
    _eventListener.Subscribe<Entity, FireProjectileMessage>(FireProjectileMessage::EventType, [&](Entity *, FireProjectileMessage *message) {
        //std::cout << "Fire ! Projectile is : " << message->getProjectileName() << std::endl;
        SpawnProjectile(*message);
    });
}

const std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() const {
    return _eventManager;
}

void EntityPool::ProcessEntities() {
    for (auto const entity : _pool)
        entity->Cycle();
}

void EntityPool::SpawnProjectile(FireProjectileMessage const &message) {
    AddEntity(message.getProjectileName(), message.getSpawnPosition());
}
