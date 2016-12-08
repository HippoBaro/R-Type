//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_SHIP_HPP
#define R_TYPE_SHIP_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class Ship : public Entity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    Ship(const std::initializer_list<void *> init);
    Ship(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};


#endif //R_TYPE_SHIP_HPP
