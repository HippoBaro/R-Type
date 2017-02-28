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

    void RegisterEntityType(uint16_t const &typeId, std::string const &entityName){
        _typesRef[typeId] = entityName;
    }

    void RegisterEntityType(const std::shared_ptr<ManagedExternalInstance<Entity>> &entity, std::string const &entityName){
        _typesRef[entity->GetInstance()->getTypeId()] = entityName;
    }

    void RegisterEntityType(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager, std::string const &entityName){
        TimeRef now;
        vec2<float> pos;
        uint16_t id;
        auto entity = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", entityName, { &id, &timer , &eventManager, &now, &pos }, "create", "destroy");
        RegisterEntityType(entity, entityName);
    }

    std::string &getTypeFromTypeId(uint16_t id){
        if (_typesRef.count(id) == 0)
            throw new std::runtime_error("Requested entity type is not registered.");
        return _typesRef[id];
    }
};


#endif //R_TYPE_ENTITYFACTORY_HPP
