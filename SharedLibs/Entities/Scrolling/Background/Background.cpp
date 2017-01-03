//
// Created by aguado_e on 12/21/16.
//

#include "Background.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

Background::Background(const std::initializer_list<void *> init) : Background(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

Background::Background(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
        Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(10000))
                            .Translate(vec2<float>(0, 0)))
            .Build();
}

void Background::Cycle() {
}

vec2<float> Background::GetRenderRect() {
    return vec2<float>(1280, 720);
}

vec2<float> Background::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void Background::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
}

uint16_t Background::getTypeId() const {
    return Entity::BACKGROUND;
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(Background)
#endif
