//
// Created by pasteu_e on 08/12/16.
//

#include "Ship.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

Ship::Ship(const std::initializer_list<void *> init) : Ship(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

Ship::Ship(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(15))
                            .Translate(vec2<float>(900, 900)))
            .Build();
}

void Ship::Cycle() {
}

RTYPE_ENTITY_REGISTER(Ship)