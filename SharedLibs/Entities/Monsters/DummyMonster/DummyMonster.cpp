//
// Created by hippolyteb on 11/25/16.
//

#include <EntityPartitionBuilder.hpp>
#include <EaseInOutCurve.hpp>
#include <EaseOutCurve.hpp>
#include "DummyMonster.hpp"

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer, vec2<int>(0, 0)).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(2))
                            .Translate(vec2<int>(500, 500))
                            .WithCurving(new EaseInOutCurve()))
            .AddSegment(PartitionSegmentBuilder()
                                  .For(std::chrono::seconds(5))
                                  .Translate(vec2<int>(-400, -400))
                                  .WithCurving(new EaseOutCurve()))
            .Loop(3)
            .Build();
}

RTYPE_ENTITY_REGISTER(DummyMonster)