//
// Created by pasteu_e on 08/12/16.
//

#include "Ship.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

Ship::Ship(const std::initializer_list<void *> init) : Ship(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                            *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                            *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                            *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                            *GetParamFromInitializerList<vec2<float>*>(init, 4))
{

}

Ship::Ship(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager) {
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