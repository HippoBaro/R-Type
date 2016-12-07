//
// Created by aguado_e on 11/22/16.
//

#ifndef R_TYPE_EVENTLISTENER_HPP
#define R_TYPE_EVENTLISTENER_HPP

#include <EventDispatcher/EventManager.hpp>

// For templating reasons, we put the code in the header directly

namespace RType {

    class EventListener {
        typedef std::map<RType::Event, std::vector<std::function<void(void *, IMessage *message)>>> callback_map;

    private:
        std::shared_ptr<RType::EventManager> _eventManager = nullptr;
        std::shared_ptr<callback_map> _callbacks;

    public:
        EventListener(std::shared_ptr<RType::EventManager> eventManager) :
                _eventManager(eventManager),
                _callbacks(std::shared_ptr<callback_map>(new callback_map())) {
            _eventManager->AddListener(_callbacks);
        }

        template<typename EntityType, typename MessageType>
        void Subscribe(RType::Event event, std::function<void(EntityType *, MessageType *message)> callback) {

            // Add the callback relative to the given event
            (*_callbacks)[event].push_back([=](void *entity, IMessage *message){
                callback((EntityType *)entity, (MessageType *)message);
            });
        }

        // Remove the callbacks for a specific event
        void Unsubscribe(RType::Event event) {
            (*_callbacks).erase(event);
        }
    };
}


#endif //R_TYPE_EVENTLISTENER_HPP
