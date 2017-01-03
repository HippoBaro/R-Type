//
// Created by hippolyteb on 12/6/16.
//

#ifndef R_TYPE_FIREPROJECTILEMESSAGE_HPP
#define R_TYPE_FIREPROJECTILEMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>

class FireProjectileMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::NEW_ENTITY;

public:
    enum Origin : uint16_t {
        PROJECTILE_ORIGIN_PLAYER,
        PROJECTILE_ORIGIN_ENVIRONEMENT
    };

private:
    const uint16_t _projectileType;
    const vec2<float> _spawnPosition;
    const uint16_t _id;
    const float _direction;
    const Origin _origin;

public:
    FireProjectileMessage(const uint16_t id, const uint16_t projectileType, const vec2<float> &spawnPosition, const float direction, const Origin origin) :
            _projectileType(projectileType), _spawnPosition(spawnPosition), _id(id), _direction(direction), _origin(origin) {}

    uint16_t getProjectileName() const {
        return _projectileType;
    }

    const vec2<float> &getSpawnPosition() const {
        return _spawnPosition;
    }

    uint16_t getId() const {
        return _id;
    }

    float getDirection() const {
        return _direction;
    }

    const Origin getOrigin() const {
        return _origin;
    }
};

#endif //R_TYPE_FIREPROJECTILEMESSAGE_HPP
