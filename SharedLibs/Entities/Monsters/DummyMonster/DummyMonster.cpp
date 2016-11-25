//
// Created by hippolyteb on 11/25/16.
//

#include "DummyMonster.hpp"

DummyMonster::DummyMonster(std::shared_ptr<Timer> &timer) : _timer(timer), _partition(EntityPartition().AddSegment(
        PartitionSegmentBuilder()
                .Begins(_timer->getCurrent())
                .Ends(_timer->getCurrent().GetRelative(std::chrono::seconds(1)))
                .From(vec2d(0, 0))
                .To(vec2d(10, 10))
                .Build(_timer)
)){

}

extern "C" DLLEXPORT DummyMonster *create(std::shared_ptr<Timer> &timer) {
    return new DummyMonster(timer);
}

extern "C" DLLEXPORT void destroy(DummyMonster *p) {
    delete p;
}