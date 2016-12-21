//
// Created by hippolyteb on 11/28/16.
//

#include <EntityPool/EntityPool.hpp>
#include <Json/Json.hpp>

void EntityPool::AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &timeRef, std::initializer_list<void *> *params) {
    auto now = timeRef;
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, { &id, &_timer , &_eventManager, &now, &pos, params }, "create", "destroy"));
    _pool.insert(std::make_pair( id, entity ));
}

void EntityPool::AddEntity(const ManagedExternalInstance<Entity> &entity) {
    _pool.insert(std::make_pair(entity->getId(), entity));
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool(std::shared_ptr<Timer> const &timer) : _timer(timer) {
    _eventListener.Subscribe<Entity, FireProjectileMessage>(FireProjectileMessage::EventType, [&](Entity *sender, FireProjectileMessage *message) {
        SpawnProjectile(*message, sender->getId());
    });
}

const std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() const {
    return _eventManager;
}

void EntityPool::ProcessEntities() {
    for(auto outer_iter=_pool.begin(); outer_iter!=_pool.end(); ++outer_iter) {
        if (outer_iter->second->ImplementTrait(Garbage))
        {
            _pool.erase(outer_iter->first);
            ProcessEntities();
            break;
        }
        outer_iter->second->Cycle();
    }
}

bool EntityPool::GarbageEntities(const ManagedExternalInstance<Entity> &entity) {
    return true;
}

void EntityPool::SpawnProjectile(FireProjectileMessage const &message, uint16_t emitterId) {
    std::initializer_list<void *> params = { &emitterId };
    AddEntity(message.getProjectileName(), message.getId(), message.getSpawnPosition(), _timer->getCurrent(), &params);
}

void EntityPool::LoadPartition(std::string const &partition) {
    RType::json j;

    j = RType::json::parse(partition);
    for (auto const &i : j["entityTypes"])
        RegisterType(i);

    for (auto const &i : j["entities"]) {
        std::string name = i["entityName"];
        vec2<float> startPos(i["startPosition"]["x"], i["startPosition"]["y"]);
        TimeRef startTime((std::chrono::milliseconds(i["startTime"])));
        uint16_t id = i["id"];
        AddEntity(name, id, startPos, startTime);
    }
}

EntityFactory &EntityPool::getFactory() {
    return _factory;
}

void EntityPool::RegisterType(std::string const &type) {
    _factory.RegisterEntityType(_timer, _eventManager, type);
}

uint16_t EntityPool::getEntityCount() {
    return (uint16_t) _pool.size();
}
