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
                            .For(std::chrono::seconds(10))
                            .Translate(vec2<float>(-2500, 0)))
            .Loop(99)
            .Build();
}

void DeathStar::Cycle() {
}

vec2<float> DeathStar::GetRenderRect() {
    return vec2<float>(500 * 0.3, 500 * 0.3);
}

vec2<float> DeathStar::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void DeathStar::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
}

uint16_t DeathStar::getTypeId() const {
    return 1;
}


#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(DeathStar)
#endif