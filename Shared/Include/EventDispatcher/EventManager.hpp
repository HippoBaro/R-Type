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
#include <EventDispatcher/IMessage.hpp>
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
    class EventManager {

    private:
        std::vector<std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(
                void *, IMessage *message)>>>>> _listeners = {};

    public:
        EventManager() {};

        void
        AddListener(std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(void *, IMessage *message)>>>> &callbacks){
            _listeners.push_back(callbacks);
        }

        void EraseListener(std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(void *, IMessage *message)>>>> &callbacks){
			size_t index = 0;
			for ( index = 0; index < _listeners.size(); index++) {
				if (_listeners[index] == callbacks) {
					_listeners.erase(_listeners.begin() + index);
					break;
				}
			}
        }

        void Emit(RType::Event event, IMessage *message, void *sender) {
			size_t index = 0;
			for (index = 0; index < _listeners.size(); index++) {
				if (_listeners[index] != nullptr)
					for (size_t inner = 0; inner < ((*_listeners[index])[event]).size(); inner++)
						((*_listeners[index])[event])[inner](sender, message);
			}
            if (message)
                delete message;
        }
    };
}


#endif //R_TYPE_EVENTMANAGER_HPP