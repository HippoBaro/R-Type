//
// Created by hippolyteb on 11/28/16.
//

#include <DrawableEntity.hpp>
#include <EntityPool/EntityPool.hpp>

void EntityPool::AddEntity(ManagedExternalInstance<Entity> &entity) {
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }
