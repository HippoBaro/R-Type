//
// Created by aguado_e on 11/22/16.
//

#ifndef R_TYPE_EVENTLISTENER_HPP
#define R_TYPE_EVENTLISTENER_HPP

#include <EventManager.hpp>

// For templating reasons, we put the code in the header directly

namespace RType {
  class IEntity;

  template <class EventType>
  class EventListener {
    typedef std::map<RType::Event, std::vector<std::function<void(IEntity&)>>> callback_map;

  private:
    std::shared_ptr<RType::EventManager> _eventManager = nullptr;
    std::shared_ptr<callback_map> _callbacks;

  public:
    EventListener(std::shared_ptr<RType::EventManager> eventManager) :
      _eventManager(eventManager),
      _callbacks(std::shared_ptr<callback_map>(new callback_map()))
    {
      std::cout << _callbacks << std::endl;
      _eventManager->AddListener(_callbacks);
    }

    void Subscribe(RType::Event event, std::function<void(EventType &)> callback)
    {
      std::function<void(IEntity&)> newCb = [callback](IEntity &data) {
        callback(static_cast<EventType &>(data));
      };

      // Add the callback relative to the given event
      (*_callbacks)[event].push_back(newCb);
    }

    // Remove the callbacks for a specific event
    void Unsubscribe(RType::Event event)
    {
      (*_callbacks).erase(event);
    }
  };
}


#endif //R_TYPE_EVENTLISTENER_HPP
