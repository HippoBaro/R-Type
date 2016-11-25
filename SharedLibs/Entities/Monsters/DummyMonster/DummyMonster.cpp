//
// Created by hippolyteb on 11/25/16.
//

#include "DummyMonster.hpp"

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(EntityPartition().AddSegment(
        PartitionSegmentBuilder()
                .Begins(_timer->getCurrent())
                .Ends(_timer->getCurrent().GetRelative(std::chrono::seconds(1)))
                .From(vec2d(0, 0))
                .To(vec2d(10, 10))
                .Build(_timer)
)){

}

extern "C" DLLEXPORT DummyMonster *create(const std::initializer_list<void *> &init) {
    for (auto i : init) // access by value, the type of i is int
        return new DummyMonster((Timer *)i);
    return new DummyMonster((Timer *) nullptr);
}

extern "C" DLLEXPORT void destroy(DummyMonster *p) {
    delete p;
}