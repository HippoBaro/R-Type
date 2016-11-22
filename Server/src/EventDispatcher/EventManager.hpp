//
// Created by aguado_e on 11/21/16.
//

#ifndef R_TYPE_EVENTDISPATCHER_HPP
#define R_TYPE_EVENTDISPATCHER_HPP

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include "Events.h"

namespace RType {

  // TODO: Put the real IEntity definition
  class IEntity {};

  class EventManager {

  private:
    std::map<RType::Event, std::vector<std::function<void(IEntity&)>>> _listeners = {};

  public:
    EventManager();

    void Register(RType::Event event, std::function<void(IEntity&)> callback);
    void Emit(RType::Event event, IEntity& data);
  };
}


#endif //R_TYPE_EVENTDISPATCHER_HPP
