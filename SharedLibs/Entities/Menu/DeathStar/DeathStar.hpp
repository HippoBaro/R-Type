//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_DEATHSTAR_HPP
#define R_TYPE_DEATHSTAR_HPP


#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class DeathStar : public Entity {
protected:
    Timer *_timer = nullptr;
    EntityPartition _partition = EntityPartition(_timer);
    RType::EventManager *_eventManager;

public:
    DeathStar(const std::initializer_list<void *> init);
    DeathStar(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};


#endif //R_TYPE_DEATHSTAR_HPP
