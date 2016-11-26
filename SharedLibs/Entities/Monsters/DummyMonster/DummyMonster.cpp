//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(timer) {
    _partition.AddSegment(
            PartitionSegmentBuilder()
                .Begins(_timer->getCurrent())
                .Ends(_timer->getCurrent().GetRelative(std::chrono::seconds(1)))
                .From(vec2d(0, 0))
                .To(vec2d(10, 10))
    ).ContinueWith(
            PartitionSegmentBuilder()
                .Begins(_timer->getCurrent().GetRelative(std::chrono::seconds(1)))
                .Ends(_timer->getCurrent().GetRelative(std::chrono::seconds(10)))
                .From(vec2d(9, 9))
                .To(vec2d(5, 5))
    ).Repeat(5);

    for (int i = 0; i < 501; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto const current = _partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
        std::cout << "Monster pos : [X:" << current.x << "; Y:" << current.y << "] TIME : " << _timer->getCurrent().getMilliseconds().count() << std::endl;
    }
}

extern "C" DLLEXPORT DummyMonster *create(const std::initializer_list<void *> init) {
    std::cout << "TEST" << std::endl;
    for (auto i : init) // access by value, the type of i is int
        return new DummyMonster((Timer *)i);
    return nullptr;
}

extern "C" DLLEXPORT void destroy(DummyMonster *p) {
    delete p;
}