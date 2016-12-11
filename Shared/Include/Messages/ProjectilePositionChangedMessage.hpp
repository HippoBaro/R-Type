//
// Created by hippolyteb on 12/10/16.
//

#ifndef R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
#define R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <vec2.hpp>
#include <string>

class ProjectilePositionChangedMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::POSITION_CHANGED_COLLISION;

private:
    vec2<float> _projectilePosition;
    const uint16_t _emitterId;

public:
    ProjectilePositionChangedMessage(const uint16_t emitterId, const vec2<float> &position) :
            _projectilePosition(position), _emitterId(emitterId) {}

    const uint16_t &getEmitterId() const {
        return _emitterId;
    }

    const vec2<float> &getProjectilePosition() const {
        return _projectilePosition;
    }

    bool TestHitBox(vec2<float> pos, vec2<float> size, uint16_t id) {
        if (_projectilePosition.Intersect(pos, pos + size) && id != _emitterId)
            return true;
        return false;
    }
};

#endif //R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
