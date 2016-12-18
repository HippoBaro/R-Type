//
// Created by pasteu_e on 08/12/16.
//

#include "Mars.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

Mars::Mars(const std::initializer_list<void *> init) : Mars(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                            *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                            *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                            *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                            *GetParamFromInitializerList<vec2<float>*>(init, 4))
{

}

Mars::Mars(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager) {
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

vec2<float> Mars::GetRenderRect() {
    return vec2<float>(500 * 0.6, 500 * 0.6);
}

vec2<float> Mars::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void Mars::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
}

uint16_t Mars::getTypeId() const {
    return 2;
}

RTYPE_ENTITY_REGISTER(Mars)