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
    EntityPartition _partition = EntityPartition(_timer);

public:
    DeathStar(const std::initializer_list<void *> init);
    DeathStar(uint16_t id, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};


#endif //R_TYPE_DEATHSTAR_HPP
