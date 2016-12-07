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

    void AddEntity(std::string const &entityName, vec2<float> const &initialPos) override;
};


#endif //R_TYPE_CLIENTENTITYPOOL_HPP
