//
// Created by aguado_e on 12/21/16.
//

#include "OrbMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include <Messages/ProjectilePositionChangedMessage.hpp>

OrbMonster::OrbMonster(const std::initializer_list<void *> init) : OrbMonster(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

OrbMonster::OrbMonster(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
  Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(10000))
                            .Translate(vec2<float>(900, 900)))
            .Build();
}

void OrbMonster::Cycle() {
}

vec2<float> OrbMonster::GetRenderRect() {
    return vec2<float>(4*16, 4*14);
}

vec2<float> OrbMonster::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void OrbMonster::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
}


uint16_t OrbMonster::getTypeId() const
{
    return this->ORB_MONSTER;
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(OrbMonster)
#endif
