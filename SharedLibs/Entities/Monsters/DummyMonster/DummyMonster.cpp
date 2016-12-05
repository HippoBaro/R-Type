//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer, vec2<float>(0, 0)).AddSegment(
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