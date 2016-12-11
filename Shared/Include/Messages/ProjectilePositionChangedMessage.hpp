//
// Created by hippolyteb on 12/10/16.
//

#ifndef R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
#define R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <vec2.hpp>
#include <string>
#include <Entities/Entity.hpp>

class ProjectilePositionChangedMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::POSITION_CHANGED_COLLISION;

private:
    vec2<float> _projectilePosition;
    const uint16_t _emitterId;
    bool _shouldDestroyProjectileOnHit;

public:
    ProjectilePositionChangedMessage(const uint16_t emitterId, const vec2<float> &position, bool shouldDestroyOnHit) :
            _projectilePosition(position), _emitterId(emitterId), _shouldDestroyProjectileOnHit(shouldDestroyOnHit) {}

    const uint16_t &getEmitterId() const {
        return _emitterId;
    }

    const vec2<float> &getProjectilePosition() const {
        return _projectilePosition;
    }

    bool TestHitBox(vec2<float> pos, vec2<float> size, uint16_t id) {
        return _projectilePosition.Intersect(pos, pos + size) && id != _emitterId;
    }

    void DidHit(Entity *sender){
        if (_shouldDestroyProjectileOnHit)
            sender->Destroy();
    }
};

#endif //R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
