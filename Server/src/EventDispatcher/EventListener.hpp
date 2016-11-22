//
// Created by aguado_e on 11/22/16.
//

#ifndef R_TYPE_EVENTLISTENER_HPP
#define R_TYPE_EVENTLISTENER_HPP


#include "EventManager.hpp"

// For templating reasons, we put the code in the header directly

namespace RType {
  template <class EventType>
  class EventListener {
    private:
      std::shared_ptr<RType::EventManager> _eventManager = nullptr;

    public:
      EventListener(std::shared_ptr<RType::EventManager> eventManager) :
        _eventManager(eventManager) {}

      void Register(RType::Event event, std::function<void(EventType&)> callback)
      {
        _eventManager->Register(event, [callback](IEntity& data) {
          callback(static_cast<EventType&>(data));
        });
      }
  };
}


#endif //R_TYPE_EVENTLISTENER_HPP
