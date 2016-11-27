//
// Created by aguado_e on 11/21/16.
//

#include <EventManager.hpp>

RType::EventManager::EventManager() {}

void RType::EventManager::AddListener(std::shared_ptr<std::map<RType::Event, std::vector<std::function<void(IEntity&)>>>> &callbacks)
{
  _listeners.push_back(callbacks);
}

void RType::EventManager::Emit(RType::Event event, RType::IEntity &data)
{
  for (auto callbacklist : _listeners)
  {
    if (callbacklist != nullptr)
      for (auto callback : (*callbacklist)[event])
        callback(data);
  }
}
