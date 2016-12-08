//
// Created by pasteu_e on 08/12/16.
//

#include "Mars.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

Mars::Mars(const std::initializer_list<void *> init) : Mars(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

Mars::Mars(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(45))
                            .Translate(vec2<float>(-2500, 0)))
            .Loop(99)
            .Build();
}

void Mars::Cycle() {
}

RTYPE_ENTITY_REGISTER(Mars)