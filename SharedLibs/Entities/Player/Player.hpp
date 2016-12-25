//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP

#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <Time/Timer.hpp>
#include <vec2.hpp>
#include <IUserControlled.hpp>
#include <PartitionSystem/EntityPartition.hpp>

class Player : public Entity, public IUserControlled {
protected:
    EntityPartition _partition = EntityPartition(_timer);
    vec2<float> _currentPosition;

public:
    Player(const std::initializer_list<void *> init);
    Player(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    virtual void Action(UserEventType event) override ;

    void Serialize(RType::Packer &packer) override;

    vec2<float> getVectorFromInput(UserEventType event);
};

#endif //R_TYPE_DUMMYMONSTER_HPP