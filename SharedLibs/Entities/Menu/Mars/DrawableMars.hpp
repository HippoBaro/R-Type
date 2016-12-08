//
// Created by pasteu_e on 07/12/16.
//

#ifndef R_TYPE_DRAWABLEPLANET_HPP
#define R_TYPE_DRAWABLEPLANET_HPP

#include <Entities/DrawableEntity.hpp>
#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class DrawableMars : public DrawableEntity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    DrawableMars(const std::initializer_list<void *> init);
    DrawableMars(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);
    void Draw(sf::RenderTexture &rect) override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;
};

#endif //R_TYPE_DRAWABLEPLANET_HPP
