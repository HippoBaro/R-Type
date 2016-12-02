//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_ENTITYPOOL_HPP
#define R_TYPE_ENTITYPOOL_HPP

#include <Interfaces/Libs/Entity.hpp>
#include <vector>
#include <memory>
#include <LibraryLoader/ManagedExternalInstance.hpp>

class EntityPool {
protected:
    std::vector<ManagedExternalInstance<Entity>> _pool = std::vector<ManagedExternalInstance<Entity>>();

public:
    virtual ~EntityPool();

public:
    virtual void AddEntity(ManagedExternalInstance<Entity> &entity);
};

#endif //R_TYPE_ENTITYPOOL_HPP
