//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_SIMPLEPROJECTILE_HPP
#define R_TYPE_SIMPLEPROJECTILE_HPP

#include <PartitionSystem/EntityPartition.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>

class SimpleProjectile : public Entity {
protected:
    EntityPartition _partition = EntityPartition(_timer);
    uint16_t _emitterId = 0;

public:
    SimpleProjectile(const std::initializer_list<void *> init);
    SimpleProjectile(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &, const std::initializer_list<void *> *);

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};


#endif //R_TYPE_SIMPLEPROJECTILE_HPP
