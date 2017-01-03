//
// Created by barre_k
//

#ifndef R_TYPE_TREERESORT_HPP
#define R_TYPE_TREERESORT_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <EventDispatcher/EventListener.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class TreeResort : public Entity {
protected:
    static constexpr int _height = 130;
    static constexpr int _width = 64;
    EntityPartition _partition = EntityPartition(_timer);
    std::unique_ptr<RType::EventListener> _eventListener;

public:
    TreeResort(const std::initializer_list<void *> init);
    TreeResort(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};

#endif //R_TYPE_TREERESORT_HPP