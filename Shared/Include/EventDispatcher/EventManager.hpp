//
// Created by aguado_e on 11/21/16.
//

#ifndef R_TYPE_EVENTMANAGER_HPP
#define R_TYPE_EVENTMANAGER_HPP

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include "Events.h"

/*
 * Usage exemple
 *
 * std::shared_ptr<RType::EventManager> e = std::shared_ptr<RType::EventManager>(new RType::EventManager);
 *
 * RType::EventListener<RType::Bullet> listener(e);
 * listener.AddListener(RType::BULLET_POS_CHANGE, [&](RType::Bullet &bullet) {
 *    // On event code here
 * });
 *
 * e->emit(BULLET_POS_CHANGE, RType::Bullet());
 *
 * listener.Unsubscribe(RType::BULLET_POS_CHANGE)
 */

namespace RType {

  // TODO: Put the real Entity definition
  class IEntity;

  class EventManager {

  private:
    std::vector<std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(IEntity&)>>>>> _listeners = {};

  public:
    EventManager();

    void AddListener(std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(IEntity&)>>>> &callbacks);
    void Emit(RType::Event event, IEntity& data);
  };
}


#endif //R_TYPE_EVENTMANAGER_HPP
