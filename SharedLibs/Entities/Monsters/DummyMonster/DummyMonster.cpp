//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>

DummyMonster::DummyMonster(const std::initializer_list<void *> init) : DummyMonster(GetParamFromInitializerList<Timer*>(init, 0), *GetParamFromInitializerList<TimeRef*>(init, 1), *GetParamFromInitializerList<vec2<float>*>(init, 2)) { }

DummyMonster::DummyMonster(Timer *timer, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(2))
                            .Translate(vec2<float>(500, 500))
                            .WithCurving(new EaseInOutCurve()))
            .AddSegment(PartitionSegmentBuilder()
                                .For(std::chrono::seconds(5))
                                .Translate(vec2<float>(-400, -400))
                                .WithCurving(new EaseOutCurve()))
            .Loop(3)
            .Build();
}

RTYPE_ENTITY_REGISTER(DummyMonster)