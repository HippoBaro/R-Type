//
// Created by hippolyteb on 11/29/16.
//

#ifndef R_TYPE_CLIENTENTITYPOOL_HPP
#define R_TYPE_CLIENTENTITYPOOL_HPP

#include <EntityPool/EntityPool.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <IDrawable.hpp>
#include "TextureBag.hpp"

class ClientEntityPool : public EntityPool {

public:
    ClientEntityPool(const std::shared_ptr<Timer> &);

public :
    virtual void Draw(sf::RenderTexture &, TextureBag &);

    virtual void AddEntity(std::string const &entityName, uint16_t, vec2<float> const &initialPos, TimeRef const &, std::initializer_list<void *> * = nullptr) override;
};


#endif //R_TYPE_CLIENTENTITYPOOL_HPP
