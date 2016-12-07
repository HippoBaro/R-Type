//
// Created by hippolyteb on 11/25/16.
//

#include "DummyMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>
#include <Messages/FireProjectileMessage.hpp>

DummyMonster::DummyMonster(const std::initializer_list<void *> init) : DummyMonster(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

DummyMonster::DummyMonster(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(2))
                            .Translate(vec2<float>(500, 500))
                            .WithCurving(new EaseInOutCurve())
                            .Fire("SimpleProjectile", 1))
            .AddSegment(PartitionSegmentBuilder()
                                .For(std::chrono::seconds(5))
                                .Translate(vec2<float>(-400, -400))
                                .WithCurving(new EaseOutCurve())
                                .Fire("SimpleProjectile", 3))
            .Loop(3)
            .Build();
}

void DummyMonster::Cycle() {
    auto now = _timer->getCurrent();
    auto segment = _partition.GetCurrentSegment(now);
    if (segment.ShouldFireNow(now)) {
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(segment.getCurrentProjectile(), segment.getLocationVector().GetTweened()), this);
    }
}

RTYPE_ENTITY_REGISTER(DummyMonster)