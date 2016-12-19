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
        uint16_t entityType;
        packer.Pack(entityType);

        if (_typesRef.count(entityType) == 0)
            throw new std::runtime_error("Requested entity type is not registered.");

        uint16_t id;
        packer.Pack(id);

        TimeRef now;
        vec2<float> pos;

        return ManagedExternalInstance<Entity>(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", _typesRef[entityType], { &id, &timer , &eventManager, &now, &pos }, "createDrawable", "destroyDrawable"));
    }

    void RegisterEntityType(uint16_t const &typeId, std::string const &entityName){
        _typesRef[typeId] = entityName;
    }
};


#endif //R_TYPE_ENTITYFACTORY_HPP
