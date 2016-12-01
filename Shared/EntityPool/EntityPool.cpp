//
// Created by hippolyteb on 11/28/16.
//

#include <vec2.hpp>
#include <DrawableEntity.hpp>
#include <iostream>
#include "EntityPool/EntityPool.hpp"
#include "LibraryLoader/ManagedExternalInstance.hpp"

void EntityPool::AddEntity(ManagedExternalInstance<Entity> &entity) {
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }
