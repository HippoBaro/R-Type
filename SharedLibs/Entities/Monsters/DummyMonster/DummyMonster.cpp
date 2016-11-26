//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"
#include "../../../../Shared/PartitionSystem/EntityPartition/EntityPartitionBuilder.hpp"
#include "../../../../Shared/Include/EaseInOutCurve.hpp"
#include "../../../../Shared/Include/LinearCurve.hpp"

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(1))
                            .From(vec2d(0, 0))
                            .To(vec2d(20, 20))
            ).ContinueWith(
                    PartitionSegmentBuilder()
                            //.WithCurving<LinearCurve>()
                            .For(std::chrono::seconds(10))
                            .To(vec2d(5, 5))
            ).Loop(2)
    .Build();

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