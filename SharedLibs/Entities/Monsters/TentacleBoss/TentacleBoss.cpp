//
// Created by aguado_e on 12/21/16.
//

#include "TentacleBoss.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <Entities/Projectiles/SimpleProjectiles/SimpleProjectile.hpp>
#include <Messages/ProjectilePositionChangedMessage.hpp>

TentacleBoss::TentacleBoss(const std::initializer_list<void *> init) : TentacleBoss(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

TentacleBoss::TentacleBoss(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
        Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(8))
                            .Translate(vec2<float>(-800, 0)))
            .AddSegment(PartitionSegmentBuilder()
                                .Translate(vec2<float>(0, 0))
                                .Fire(Entity::BIG_PROJECTILE, 8)
                                .For(std::chrono::seconds(100000)))
            .Build();

    _eventListener->Subscribe<SimpleProjectile, ProjectilePositionChangedMessage>(
            ProjectilePositionChangedMessage::EventType,
            [&](SimpleProjectile *projectile, ProjectilePositionChangedMessage *message) {
                if (message->TestHitBox(GetPosition(), GetRenderRect(), FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT)
                        && GetPosition().x < 1280)
                {
                    message->DidHit(projectile);
                    this->takeDamage(10);
                }
            }
    );
}

void TentacleBoss::Cycle() {
    auto now = _timer->getCurrent();
    if (_partition.ShouldFire(now)) {
        auto segment = _partition.GetCurrentSegment(now);
        std::uniform_int_distribution<uint16_t > uni(100, UINT16_MAX);
        auto pos = segment->getLocationVector().GetTweened();
        pos.x += 100;
        pos.y += 50;
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), segment->getCurrentProjectile(), pos, 20, FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT), this);
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), segment->getCurrentProjectile(), pos, 0, FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT), this);
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), segment->getCurrentProjectile(), pos, 340, FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT), this);
    }
}

vec2<float> TentacleBoss::GetRenderRect() {
    return vec2<float>(4 * 256, 4 * 142);
}

vec2<float> TentacleBoss::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void TentacleBoss::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
    packer.Pack(_life);
}

uint16_t TentacleBoss::getTypeId() const {
    return Entity::TENTACLE_BOSS;
}

void TentacleBoss::takeDamage(const uint16_t value)
{
    _life -= value;
    if (_life <= 0)
        this->Destroy();
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(TentacleBoss)
#endif
