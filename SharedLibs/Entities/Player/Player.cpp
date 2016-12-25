//
// Created by hippolyteb on 11/25/16.
//

#include "Player.hpp"
#include <Messages/FireProjectileMessage.hpp>
#include <PartitionSystem/EntityPartition.hpp>
#include <PartitionSystem/EntityPartitionBuilder.hpp>

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(Player)
#endif

Player::Player(const std::initializer_list<void *> init) : Player(*GetParamFromInitializerList<uint16_t  *>(init, 0),
                                                                  *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                  *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                  *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                  *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

Player::Player(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager),
                                                                                                                                                                         _currentPosition(startPosition) {
    auto now = _timer->getCurrent();
    _partition = EntityPartitionBuilder(_timer, now, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .For(std::chrono::milliseconds(50))
                            .Translate(vec2<float>()))
            .Build();
}

void Player::Cycle() { }

vec2<float> Player::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> Player::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

uint16_t Player::getTypeId() const {
    return 5;
}

void Player::Action(UserEventType event){
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    auto now = _timer->getCurrent();
    _partition = EntityPartitionBuilder(_timer, now, pos).AddSegment(
                    PartitionSegmentBuilder()
                            .For(std::chrono::milliseconds(50))
                            .Translate(getVectorFromInput(event)))
            .Build();

    NeedSynch();
}

vec2<float> Player::getVectorFromInput(UserEventType event) {
    constexpr float velocity = 15;

    switch (event) {
        case USER_UP:
            return vec2<float>(0, -velocity);
        case USER_DOWN:
            return vec2<float>(0, velocity);
        case USER_RIGHT:
            return vec2<float>(velocity, 0);
        case USER_LEFT:
            return vec2<float>(-velocity, 0);
        default:
            return vec2<float>();
    }
}

void Player::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
}