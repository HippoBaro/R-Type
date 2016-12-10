//
// Created by hippolyteb on 11/25/16.
//

#include "Player.hpp"
#include <Messages/FireProjectileMessage.hpp>

Player::Player(const std::initializer_list<void *> init) : Player(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

Player::Player(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {

}

void Player::Cycle() {
//    auto now = _timer->getCurrent();
//    if (_partition.ShouldFire(now)) {
//        auto segment = _partition.GetCurrentSegment(now);
//        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(segment->getCurrentProjectile(), segment->getLocationVector().GetTweened()), this);
//    }
}

RTYPE_ENTITY_REGISTER(Player)