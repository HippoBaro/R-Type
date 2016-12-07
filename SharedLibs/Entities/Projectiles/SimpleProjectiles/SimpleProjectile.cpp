//
// Created by hippolyteb on 12/5/16.
//

#include "SimpleProjectile.hpp"

#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>
#include <iostream>

SimpleProjectile::SimpleProjectile(const std::initializer_list<void *> init) : SimpleProjectile(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

SimpleProjectile::SimpleProjectile(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(2))
                            .Translate(vec2<float>(1280, 0))
                            .WithCurving(new EaseInOutCurve()))
            .Build();
}

void SimpleProjectile::Cycle() {
    if (_partition.isPartitionPlayed(_timer->getCurrent()))
        this->Destroy();
}

SimpleProjectile::~SimpleProjectile() {
}

RTYPE_ENTITY_REGISTER(SimpleProjectile)