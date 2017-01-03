//
// Created by barre_k
//

#include "SpaceShip.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

SpaceShip::SpaceShip(const std::initializer_list<void *> init) : SpaceShip(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

SpaceShip::SpaceShip(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
        Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(10000))
                            .Translate(vec2<float>(0, 0)))
            .Build();
}

void SpaceShip::Cycle() {
}

vec2<float> SpaceShip::GetRenderRect() {
    return vec2<float>(4 * _width, 4 * _height);
}

vec2<float> SpaceShip::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void SpaceShip::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
}

uint16_t SpaceShip::getTypeId() const {
    return Entity::SPACESHIP;
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(SpaceShip)
#endif
