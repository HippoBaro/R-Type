//
// Created by pasteu_e on 08/12/16.
//

#include "DeathStar.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

DeathStar::DeathStar(const std::initializer_list<void *> init) : DeathStar(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                           *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                           *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                           *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                           *GetParamFromInitializerList<vec2<float>*>(init, 4))
{

}

DeathStar::DeathStar(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(80))
                            .Translate(vec2<float>(-2500, 0)))
            .Loop(99)
            .Build();
}

void DeathStar::Cycle() {
}

void DeathStar::Serialize(RType::Packer &packer) {
}

RTYPE_ENTITY_REGISTER(DeathStar)