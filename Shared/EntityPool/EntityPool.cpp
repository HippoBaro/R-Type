//
// Created by hippolyteb on 11/28/16.
//

#include <Interfaces/Libs/DrawableEntity.hpp>
#include <EntityPool/EntityPool.hpp>

void EntityPool::AddEntity(ManagedExternalInstance<Entity> &entity) {
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool() {
    //_eventListener.Subscribe(RType::BULLET_DAMAGE_CHANGE)
}

const std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() const {
    return _eventManager;
}
