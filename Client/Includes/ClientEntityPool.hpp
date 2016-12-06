//
// Created by hippolyteb on 11/29/16.
//

#ifndef R_TYPE_CLIENTENTITYPOOL_HPP
#define R_TYPE_CLIENTENTITYPOOL_HPP

#include <EntityPool/EntityPool.hpp>
#include <EventDispatcher/EventManager.hpp>

class ClientEntityPool : public EntityPool {
private:
    RType::EventManager _eventManager = RType::EventManager();
public :
    virtual void Draw(sf::RenderTexture &target);
};


#endif //R_TYPE_CLIENTENTITYPOOL_HPP
