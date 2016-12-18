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

vec2<float> Ship::GetRenderRect() {
    return vec2<float>(500 * 0.3, 500 * 0.3);
}

vec2<float> Ship::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void Ship::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
}

uint16_t Ship::getTypeId() const {
    return 3;
}

RTYPE_ENTITY_REGISTER(Ship)