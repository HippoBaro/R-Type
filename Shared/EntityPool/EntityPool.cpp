//
// Created by hippolyteb on 11/28/16.
//

#include <EntityPool/EntityPool.hpp>

void EntityPool::AddEntity(std::string const &entityName, vec2<float> const &initialPos) {
    auto now = _timer->getCurrent();
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, {_timer.get() , _eventManager.get(), &now, &pos }, "create", "destroy"));
    _pool.push_back(entity);
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool(std::shared_ptr<Timer> const &timer) : _timer(timer) {
    _eventListener.Subscribe<Entity, FireProjectileMessage>(FireProjectileMessage::EventType, [&](Entity *, FireProjectileMessage *message) {
        SpawnProjectile(*message);
    });
}

const std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() const {
    return _eventManager;
}

void EntityPool::ProcessEntities() {
    for (unsigned int i = 0; i < _pool.size(); ++i) {
        if (_pool[i]->ImplementTrait(Garbage))
        {
            _pool.erase(_pool.begin() + i);
            ProcessEntities();
            break;
        }
        _pool[i]->Cycle();
        GarbageEntities(_pool[i]);
    }
}

bool EntityPool::GarbageEntities(const ManagedExternalInstance<Entity> &entity) {
    return true;
}

void EntityPool::SpawnProjectile(FireProjectileMessage const &message) {
    AddEntity(message.getProjectileName(), message.getSpawnPosition());
}
