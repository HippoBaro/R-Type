//
// Created by hippolyteb on 11/28/16.
//

#include <Entities/DrawableEntity.hpp>
#include <EntityPool/EntityPool.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include <iostream>

void EntityPool::AddEntity(ManagedExternalInstance<Entity> &entity) {
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool() {
    _eventListener.Subscribe<Entity, FireProjectileMessage>(FireProjectileMessage::EventType, [&](Entity *, FireProjectileMessage *message) {
        std::cout << "Message !" << std::endl;
    });
}

const std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() const {
    return _eventManager;
}

void EntityPool::ProcessEntities() {
    for (auto const entity : _pool)
        entity->Cycle();
}
