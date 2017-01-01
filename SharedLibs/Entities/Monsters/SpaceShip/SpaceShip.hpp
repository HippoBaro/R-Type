//
// Created by barre_k
//

#ifndef R_TYPE_SPACESHIP_HPP
#define R_TYPE_SPACESHIP_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <EventDispatcher/EventListener.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class SpaceShip : public Entity {
protected:
    static constexpr int _height = 21;
    static constexpr int _width = 24;
    EntityPartition _partition = EntityPartition(_timer);
    std::unique_ptr<RType::EventListener> _eventListener;

public:
    SpaceShip(const std::initializer_list<void *> init);
    SpaceShip(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};

#endif //R_TYPE_SPACESHIP_HPP