//
// Created by hippolyteb on 12/23/16.
//

#ifndef R_TYPE_ENTITYPACKER_HPP
#define R_TYPE_ENTITYPACKER_HPP

#include <Serializer/Packer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <Entities/Entity.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include <EntityFactory/EntityFactory.hpp>

class EntityPacker {
private:
    RType::Packer _packer;
    EntityFactory _factory;

    std::string _type;
    uint16_t _typeId;

    uint64_t _timeStamp;

    uint16_t _entityId;

    std::shared_ptr<ManagedExternalInstance<Entity>> _entity = nullptr;

public:
    EntityPacker() : _packer(), _factory(), _type(), _typeId(0), _timeStamp(0), _entityId(0), _entity() {}
    EntityPacker(const RType::Packer &packer, const EntityFactory &factory) : _packer(packer), _factory(factory), _entity() {
        _packer.Pack(_timeStamp);
        _packer.Pack(_typeId);
        _packer.Pack(_entityId);
        _type = _factory.getTypeFromTypeId(_typeId);
    }

    void UnpackEntity(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager) {
        TimeRef now = 0;
        vec2<float> pos;

        _entity = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", _type, { &_entityId, &timer , &eventManager, &now, &pos }, "create", "destroy");
        _entity->GetInstance()->Serialize(_packer);
    }

    std::shared_ptr<ManagedExternalInstance<Entity>> &GetEntity(std::shared_ptr<Timer> &timer, std::shared_ptr<RType::EventManager> &eventManager) {
        if (_entity == nullptr)
            UnpackEntity(timer, eventManager);
        return _entity;
    }

    const std::string &getType() const {
        return _type;
    }

    uint16_t getTypeId() const {
        return _typeId;
    }

    long getTimeStamp() const {
        return _timeStamp;
    }

    uint16_t getEntityId() const {
        return _entityId;
    }
};

#endif //R_TYPE_ENTITYPACKER_HPP
