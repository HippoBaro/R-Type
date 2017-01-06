//
// Created by aguado_e on 12/21/16.
//

#include "OrbMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include <Messages/ProjectilePositionChangedMessage.hpp>
#include <Entities/Projectiles/SimpleProjectiles/SimpleProjectile.hpp>

OrbMonster::OrbMonster(const std::initializer_list<void *> init) : OrbMonster(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

OrbMonster::OrbMonster(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
  Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(15))
                            .Translate(vec2<float>(-1400.f, -100.f))
                            .Fire(Entity::SIMPLE_PROJECTILE, 5))
    .Build();

    _eventListener->Subscribe<SimpleProjectile, ProjectilePositionChangedMessage>(
            ProjectilePositionChangedMessage::EventType,
            [&](SimpleProjectile *projectile, ProjectilePositionChangedMessage *message) {
                if (message->TestHitBox(GetPosition(), GetRenderRect(), FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT)) {
                    message->DidHit(projectile);
                    this->takeDamage(10);
                }
            }
    );
}

void OrbMonster::Cycle() {
    auto now = _timer->getCurrent();
    if (_partition.ShouldFire(now)) {
        auto segment = _partition.GetCurrentSegment(now);
        std::uniform_int_distribution<uint16_t > uni(100, UINT16_MAX);
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), segment->getCurrentProjectile(), segment->getLocationVector().GetTweened(), 180, FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT), this);
    }
}

vec2<float> OrbMonster::GetRenderRect() {
    return vec2<float>(4*16, 4*14);
}

vec2<float> OrbMonster::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void OrbMonster::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
    packer.Pack(_life);
}

uint16_t OrbMonster::getTypeId() const
{
    return Entity::ORB_MONSTER;
}

void OrbMonster::takeDamage(const uint16_t value) {
    _life -= value;
    if (_life <= 0)
        this->Destroy();
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(OrbMonster)
#endif
