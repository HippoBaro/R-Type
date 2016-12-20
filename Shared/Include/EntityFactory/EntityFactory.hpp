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
    ManagedExternalInstance<Entity> CreateFromPayload(RType::Packer &packer, std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager);

    void RegisterEntityType(uint16_t const &typeId, std::string const &entityName);
    void RegisterEntityType(const ManagedExternalInstance<Entity> &entity, std::string const &entityName);
    void RegisterEntityType(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager, std::string const &entityName);
};


#endif //R_TYPE_ENTITYFACTORY_HPP
