//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_MARS_HPP
#define R_TYPE_MARS_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class Mars : public Entity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    Mars(const std::initializer_list<void *> init);
    Mars(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};

#endif //R_TYPE_MARS_HPP
