//
// Created by hippolyteb on 12/19/16.
//

#include "EntityFactory/EntityFactory.hpp"

ManagedExternalInstance<Entity> EntityFactory::CreateFromPayload(RType::Packer &packer, std::shared_ptr<Timer> &timer,
                                                                 std::shared_ptr<RType::EventManager> &eventManager) {
    uint16_t entityType;
    packer.Pack(entityType);

    if (_typesRef.count(entityType) == 0)
        throw new std::runtime_error("Requested entity type is not registered.");

    uint16_t id;
    packer.Pack(id);

    TimeRef now;
    vec2<float> pos;

    auto entity = ManagedExternalInstance<Entity>(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", _typesRef[entityType], { &id, &timer , &eventManager, &now, &pos }, "createDrawable", "destroyDrawable"));
    entity->Serialize(packer);
    return entity;
}

void EntityFactory::RegisterEntityType(uint16_t const &typeId, std::string const &entityName) {
    _typesRef[typeId] = entityName;
}

void EntityFactory::RegisterEntityType(const ManagedExternalInstance<Entity> &entity, std::string const &entityName) {
    _typesRef[entity->getTypeId()] = entityName;
}

void
EntityFactory::RegisterEntityType(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager,
                                  std::string const &entityName) {
    TimeRef now;
    vec2<float> pos;
    uint16_t id;
    auto entity = ManagedExternalInstance<Entity>(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, { &id, &timer , &eventManager, &now, &pos }, "create", "destroy"));
    RegisterEntityType(entity, entityName);
}
