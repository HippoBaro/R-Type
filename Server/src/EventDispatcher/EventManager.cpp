//
// Created by aguado_e on 11/21/16.
//

#include "EventManager.hpp"

RType::EventManager::EventManager() {}

void RType::EventManager::Register(RType::Event event, std::function<void(RType::IEntity &)> callback)
{
  _listeners[event].push_back(callback);
}

void RType::EventManager::Emit(RType::Event event, RType::IEntity &data)
{
  for (auto i : _listeners[event])
    i(data);
}
