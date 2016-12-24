//
// Created by hippolyteb on 11/25/16.
//

#include "Player.hpp"
#include <Messages/FireProjectileMessage.hpp>

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(Player)
#endif

Player::Player(const std::initializer_list<void *> init) : Player(*GetParamFromInitializerList<uint16_t  *>(init, 0),
                                                                  *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                  *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                  *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                  *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

Player::Player(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager),
                                                                                                                                                                         _currentPosition(startPosition) {}

void Player::Cycle() { }

vec2<float> Player::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> Player::GetPosition() {
    return _currentPosition;
}

uint16_t Player::getTypeId() const {
    return 5;
}

void Player::Action(UserEventType event){
    switch (event) {
        case USER_UP:
            _currentPosition = vec2<float>(_currentPosition.x, _currentPosition.y - 5);
            break;
        case USER_DOWN:
            _currentPosition = vec2<float>(_currentPosition.x, _currentPosition.y + 5);
            break;
        case USER_RIGHT:
            _currentPosition = vec2<float>(_currentPosition.x + 5, _currentPosition.y);
            break;
        case USER_LEFT:
            _currentPosition = vec2<float>(_currentPosition.x - 5, _currentPosition.y);
            break;
        case USER_SPACE:
            break;

        default:
            break;
    }
    NeedSynch();
}

void Player::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _currentPosition.Serialize(packer);
}