//
// Created by hippolyteb on 11/28/16.
//

#include <EntityPool/EntityPool.hpp>
#include <Json/Json.hpp>

void EntityPool::AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &timeRef, std::initializer_list<void *> *params) {
    auto now = timeRef;
    auto pos = initialPos;
    auto entity = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, { &id, &_timer , &_eventManager, &now, &pos, params }, "create", "destroy");
    _pool.insert(std::make_pair(id, entity));
}

void EntityPool::AddEntity(const std::shared_ptr<ManagedExternalInstance<Entity>> &entity) {
    _pool.erase(entity->GetInstance()->getId());
    _pool.insert(std::make_pair(entity->GetInstance()->getId(), entity));
}

EntityPool::~EntityPool() { }

EntityPool::EntityPool(std::shared_ptr<Timer> const &timer) : _timer(timer) {
    _eventListener.Subscribe<Entity, FireProjectileMessage>(FireProjectileMessage::EventType, [&](Entity *sender, FireProjectileMessage *message) {
        SpawnProjectile(*message, sender->getId());
    });
}

std::shared_ptr<RType::EventManager> &EntityPool::getEventManager() {
    return _eventManager;
}

void EntityPool::ProcessEntities() {
    for(auto outer_iter=_pool.begin(); outer_iter!=_pool.end(); ++outer_iter) {
        if (outer_iter->second->GetInstance()->ImplementTrait(Garbage))
        {
            _pool.erase(outer_iter->first);
            ProcessEntities();
            break;
        }
        outer_iter->second->GetInstance()->Cycle();
    }
}

bool EntityPool::GarbageEntities(const ManagedExternalInstance<Entity> &entity) {
    return true;
}

void EntityPool::SpawnProjectile(FireProjectileMessage const &message, uint16_t emitterId) {
    if (_pool.count(message.getId()) > 0)
        return;
    auto direction = message.getDirection();
    std::initializer_list<void *> params = { &emitterId, &direction };
    AddEntity(_factory.getTypeFromTypeId(message.getProjectileName()), message.getId(), message.getSpawnPosition(), _timer->getCurrent(), &params);
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

bool EntityPool::Exist(const uint16_t id) {
    return _pool.count(id) > 0;
}

bool EntityPool::isPlayer(const uint16_t id) {
    return _pool.count(id) > 0 && getEntityById(id)->GetInstance()->getTypeId() == Entity::PLAYER;
}

std::shared_ptr<ManagedExternalInstance<Entity>> &EntityPool::getEntityById(uint16_t id) {
    return _pool[id];
}
