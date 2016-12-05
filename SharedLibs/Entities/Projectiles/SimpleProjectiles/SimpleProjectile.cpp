//
// Created by hippolyteb on 12/5/16.
//

#include "SimpleProjectile.hpp"

#include <EntityPartitionBuilder.hpp>
#include <EaseInOutCurve.hpp>
#include <EaseOutCurve.hpp>
#include <Base.h>
#include "SimpleProjectile.hpp"

SimpleProjectile::SimpleProjectile(Timer *timer) : _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(5))
                            .From(vec2<int>(0, 0))
                            .To(vec2<int>(500, 500))
                            .WithCurving(new EaseInOutCurve()))
            .ContinueWith(PartitionSegmentBuilder()
                                  .From(vec2<int>(500, 500))
                                  .For(std::chrono::seconds(10))
                                  .To(vec2<int>(100, 90))
                                  .WithCurving(new EaseOutCurve()))
            .Loop(2)
            .Build();
}

RTYPE_ENTITY_REGISTER(SimpleProjectile)