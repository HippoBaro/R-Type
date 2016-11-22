//
// Created by aguado_e on 11/21/16.
//

#ifndef R_TYPE_EVENTMANAGER_HPP
#define R_TYPE_EVENTMANAGER_HPP

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include "Events.h"

/*
 * Usage exemple
 *
 *
 * std::shared_ptr<RType::EventManager> e = std::shared_ptr<RType::EventManager>(new RType::EventManager);
 * RType::EventListener<RType::Bullet> listener(e);
 * listener->Register(RType::BULLET_POS_CHANGE, [&](RType::Bullet &bullet) {
 *    // On event code here
 * });
 *
 */

namespace RType {

  // TODO: Put the real IEntity definition
  class IEntity;

  class EventManager {

  private:
    std::map<RType::Event, std::vector<std::function<void(IEntity&)>>> _listeners = {};

  public:
    EventManager();

    void Register(RType::Event event, std::function<void(IEntity&)> callback);
    void Emit(RType::Event event, IEntity& data);
  };
}


#endif //R_TYPE_EVENTMANAGER_HPP
