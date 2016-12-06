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
    std::shared_ptr<RType::EventManager> _eventManager = std::make_shared<RType::EventManager>();
    RType::EventListener _eventListener = RType::EventListener(_eventManager);

public:
    EntityPool();

public:
    virtual ~EntityPool();

public:
    virtual void AddEntity(ManagedExternalInstance<Entity> &entity);

public:
    const std::shared_ptr<RType::EventManager> &getEventManager() const;
};

#endif //R_TYPE_ENTITYPOOL_HPP
