//
// Created by aguado_e on 12/21/16.
//

#ifndef R_TYPE_TENTACLEBOSS_HPP
#define R_TYPE_TENTACLEBOSS_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <EventDispatcher/EventListener.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class Background : public Entity {
protected:
    EntityPartition _partition = EntityPartition(_timer);
    std::unique_ptr<RType::EventListener> _eventListener;

public:
    Background(const std::initializer_list<void *> init);
    Background(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};

#endif //R_TYPE_TENTACLEBOSS_HPP