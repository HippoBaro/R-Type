//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "Player.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <PartitionSystem/Tween/Curve/EaseInOutCurve.hpp>
#include <PartitionSystem/Tween/Curve/EaseOutCurve.hpp>

Player::Player(Timer *timer) : _timer(timer), _partition(timer) {
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

RTYPE_ENTITY_REGISTER(Player)