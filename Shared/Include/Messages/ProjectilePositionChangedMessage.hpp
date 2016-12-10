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
    const vec2<float> _projectilePosition;

public:
    ProjectilePositionChangedMessage(const vec2<float> &position) :
            _projectilePosition(position) {}

    const vec2<float> &getProjectilePosition() const {
        return _projectilePosition;
    }
};

#endif //R_TYPE_PROJECTILEPOSITIONCHANGEDMESSAGE_HPP
