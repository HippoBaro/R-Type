//
// Created by hippolyteb on 12/5/16.
//

#ifndef R_TYPE_BIGPROJECTILE_HPP
#define R_TYPE_BIGPROJECTILE_HPP

#include <PartitionSystem/EntityPartition.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <Messages/FireProjectileMessage.hpp>

class BigProjectile : public Entity {
protected:
    EntityPartition _partition = EntityPartition(_timer);
    FireProjectileMessage::Origin _origin = FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT;

public:
    BigProjectile(const std::initializer_list<void *> init);
    BigProjectile(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &, const std::initializer_list<void *> *);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};


#endif //R_TYPE_BIGPROJECTILE_HPP
