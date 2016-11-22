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

  class IEntity {
  public:
    IEntity(int a) : a(a){}
    int a;
  };

  class Bullet : public IEntity {
  public:
    Bullet(int a) : IEntity(a) {}
  };



  class EventManager {

  private:
    std::map<RType::Event, std::vector<std::function<void(IEntity&)>>> _listeners;

  public:
    EventManager() {}

    void Register(RType::Event event, std::function<void(IEntity&)> callback) {
      _listeners[event].push_back(callback);
    }

    void Emit(RType::Event event, IEntity& data) {
      for (auto i : _listeners[event]) {
        i(data);
      }
    }
  };

  class EventListener {
  private:
    std::shared_ptr<RType::EventManager> _eventManager;

  public:
    EventListener(std::shared_ptr<RType::EventManager> eventManager) : _eventManager(eventManager) {}

    template <typename EventType>
    void Register(RType::Event event, std::function<void(EventType&)> callback) {
      _eventManager->Register(event, [callback](IEntity& data) {
        callback(static_cast<EventType&>(data));
      });
    }
  };

}


#endif //R_TYPE_EVENTDISPATCHER_HPP
