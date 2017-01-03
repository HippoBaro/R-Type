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
#include "FireProjectileMessage.hpp"

class ProjectilePositionChangedMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::POSITION_CHANGED_COLLISION;

private:
    vec2<float> _projectilePosition;
    const FireProjectileMessage::Origin _origin;
    bool _shouldDestroyProjectileOnHit;

public:
    ProjectilePositionChangedMessage(const FireProjectileMessage::Origin origin, const vec2<float> &position, bool shouldDestroyOnHit) :
            _projectilePosition(position), _origin(origin), _shouldDestroyProjectileOnHit(shouldDestroyOnHit) {}

    FireProjectileMessage::Origin getOrigin() const {
        return _origin;
    }

    const vec2<float> &getProjectilePosition() const {
        return _projectilePosition;
    }

    bool TestHitBox(vec2<float> pos, vec2<float> size, FireProjectileMessage::Origin entityOrigin) {
        return _projectilePosition.Intersect(pos, pos + size) && entityOrigin != _origin;
    }

    void DidHit(Entity *sender){
        if (_shouldDestroyProjectileOnHit)
            sender->Destroy();
    }
};

#endif //R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
