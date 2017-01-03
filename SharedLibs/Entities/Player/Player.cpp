//
// Created by hippolyteb on 11/25/16.
//

#include "Player.hpp"
#include <Messages/FireProjectileMessage.hpp>
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

void Player::Cycle() {
    if (_timer->getCurrent().getMilliseconds().count() - _lastUserInput.getMilliseconds().count() > 10000)
        ImplementTrait(Trait::Garbage);
    if (_shouldFire) {
        _shouldFire = false;
        auto segment = _partition.GetCurrentSegment(_timer->getCurrent());
        std::uniform_int_distribution<uint16_t > uni(100, UINT16_MAX);
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), Entity::SIMPLE_PROJECTILE, segment->getLocationVector().GetTweened(), 0), this);
    }
}

vec2<float> Player::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> Player::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

uint16_t Player::getTypeId() const {
    return Entity::PLAYER;
}

void Player::Action(std::set<UserEventType> events) {
    _lastUserInput = _timer->getCurrent();
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    auto now = _timer->getCurrent();
    _partition = EntityPartitionBuilder(_timer, now, pos).AddSegment(
                    PartitionSegmentBuilder()
                            .For(std::chrono::milliseconds(50))
                            .Translate(getVectorFromInput(events)))
            .Build();
    if (events.size() > 0)
        NeedSynch();
}

vec2<float> Player::getVectorFromInput(std::set<UserEventType> &events) {
    constexpr float velocity = 15;
    vec2<float> direction;

    if (events.count(USER_UP) > 0)
        direction = vec2<float>(direction.x, direction.y - velocity);
    if (events.count(USER_DOWN) > 0)
        direction = vec2<float>(direction.x, direction.y + velocity);
    if (events.count(USER_RIGHT) > 0)
        direction =  vec2<float>(direction.x + velocity, direction.y);
    if (events.count(USER_LEFT) > 0)
        direction = vec2<float>(direction.x - velocity,direction.y);
    if (events.count(USER_SPACE) > 0)
        _shouldFire = true;

    return direction;
}

void Player::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
}