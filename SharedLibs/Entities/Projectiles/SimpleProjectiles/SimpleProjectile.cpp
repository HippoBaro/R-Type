//
// Created by hippolyteb on 12/5/16.
//

#include "SimpleProjectile.hpp"

#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>
#include <iostream>
#include <Messages/ProjectilePositionChangedMessage.hpp>

SimpleProjectile::SimpleProjectile(const std::initializer_list<void *> init) :
        SimpleProjectile(*GetParamFromInitializerList<uint16_t *>(init, 0),
                         GetParamFromInitializerList<Timer*>(init, 1),
                         GetParamFromInitializerList<RType::EventManager*>(init, 2),
                         *GetParamFromInitializerList<TimeRef*>(init, 3),
                         *GetParamFromInitializerList<vec2<float>*>(init, 4),
                         GetParamFromInitializerList<std::initializer_list<void *>*>(init, 5))
{

}

SimpleProjectile::SimpleProjectile(uint16_t id,
                                   Timer *timer,
                                   RType::EventManager *eventManager,
                                   TimeRef const &timeRef,
                                   vec2<float> const &startPosition,
                                   const std::initializer_list<void *> *params) : Entity(id, timer, eventManager) {
    _emitterId = *GetParamFromInitializerList<uint16_t *>(*params, 0);
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(2))
                            .Translate(vec2<float>(1280, 0)))
            .Build();
}

void SimpleProjectile::Cycle() {
    if (_partition.isPartitionPlayed(_timer->getCurrent()))
        this->Destroy();
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    _eventManager->Emit(ProjectilePositionChangedMessage::EventType, new ProjectilePositionChangedMessage(_emitterId, pos, true), this);
}

SimpleProjectile::~SimpleProjectile() {
}

RTYPE_ENTITY_REGISTER(SimpleProjectile)