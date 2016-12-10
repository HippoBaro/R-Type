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

class Player : public Entity {
protected:
    Timer *_timer = nullptr;
    RType::EventManager *_eventManager;

public:
    Player(const std::initializer_list<void *> init);
    Player(Timer *, RType::EventManager *, TimeRef const &, vec2<float> const &);

    void Cycle() override;
};

#endif //R_TYPE_DUMMYMONSTER_HPP