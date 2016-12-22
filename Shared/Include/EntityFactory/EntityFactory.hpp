//
// Created by hippolyteb on 12/19/16.
//

#ifndef R_TYPE_ENTITYFACTORY_HPP
#define R_TYPE_ENTITYFACTORY_HPP

#include <Entities/Entity.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>

class EntityFactory {

private:
    std::map<uint16_t, std::string> _typesRef ;

public:
    EntityFactory() : _typesRef() {}

public:
    ManagedExternalInstance<Entity> CreateFromPayload(RType::Packer &packer, std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager) {
        long time = 0;
        packer.Pack(time);

        uint16_t entityType = 0;
        packer.Pack(entityType);

        uint16_t id = 0;
        packer.Pack(id);

        TimeRef now = 0;
        vec2<float> pos;

		if (_typesRef.count(entityType) == 0)
			throw new std::runtime_error("Requested entity type is not registered.");

        timer->RecalibrateOrigin(time);
        auto entity = ManagedExternalInstance<Entity>(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", _typesRef[entityType], { &id, &timer , &eventManager, &now, &pos }, "create", "destroy"));
        entity->Serialize(packer);
        return entity;
    }

    void RegisterEntityType(uint16_t const &typeId, std::string const &entityName){
        _typesRef[typeId] = entityName;
    }

    void RegisterEntityType(const ManagedExternalInstance<Entity> &entity, std::string const &entityName){
        _typesRef[entity->getTypeId()] = entityName;
    }

    void RegisterEntityType(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager, std::string const &entityName){
        TimeRef now;
        vec2<float> pos;
        uint16_t id;
        auto entity = ManagedExternalInstance<Entity>(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, { &id, &timer , &eventManager, &now, &pos }, "create", "destroy"));
        RegisterEntityType(entity, entityName);
    }
};


#endif //R_TYPE_ENTITYFACTORY_HPP
