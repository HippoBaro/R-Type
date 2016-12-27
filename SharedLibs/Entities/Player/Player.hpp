//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP

#include <Entities/Entity.hpp>
#include <IUserControlled.hpp>
#include <PartitionSystem/EntityPartition.hpp>
#include <Base.h>

class Player : public Entity, public IUserControlled {
protected:
    EntityPartition _partition = EntityPartition(_timer);
    vec2<float> _currentPosition;
    bool _shouldFire = false;

public:
    Player(const std::initializer_list<void *> init);
    Player(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    virtual void Action(std::set<UserEventType> events) override ;

    void Serialize(RType::Packer &packer) override;

    vec2<float> getVectorFromInput(std::set<UserEventType> &events);
};

#endif //R_TYPE_PLAYER_HPP