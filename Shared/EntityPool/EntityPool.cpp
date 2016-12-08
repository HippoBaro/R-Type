//
// Created by hippolyteb on 11/28/16.
//

#include <EntityPool/EntityPool.hpp>
#include <Json/Json.hpp>

void EntityPool::AddEntity(std::string const &entityName, vec2<float> const &initialPos, TimeRef const &timeRef) {
    auto now = timeRef;
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
    AddEntity(message.getProjectileName(), message.getSpawnPosition(), _timer->getCurrent());
}

void EntityPool::LoadPartition(std::string const &partition) {
    RType::json j;

    auto json = "{\n"
            "\t\"partitionName\":\"TestPartition\",\n"
            "\t\"backgroundTheme\":\"test.ogg\",\n"
            "\t\"backgroundEntity\": \n"
            "\t\t{\n"
            "\t\t\t\"entityName\":\"testEntity\",\n"
            "\t\t\t\"startPosition\": {\n"
            "\t\t\t\t\"x\":0,\n"
            "\t\t\t\t\"y\":0\n"
            "\t\t}\n"
            "\t},\n"
            "\t\"entities\":[\n"
            "\t\t{\n"
            "\t\t\t\"entityName\":\"DummyMonster\",\n"
            "\t\t\t\"startPosition\": {\n"
            "\t\t\t\t\"x\":0,\n"
            "\t\t\t\t\"y\":0\n"
            "\t\t\t},\n"
            "\t\t\t\"startTime\":1000\n"
            "\t\t}\n"
            "\t]\n"
            "}";

    j = RType::json::parse(json);
    for (auto const &i : j["entities"]) {
        std::string name = i["entityName"];
        vec2<float> startPos(i["startPosition"]["x"], i["startPosition"]["y"]);
        TimeRef startTime(std::chrono::milliseconds(i[std::string("startTime")]));
        AddEntity(name, startPos, startTime);
    }
}
