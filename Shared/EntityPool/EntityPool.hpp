//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_ENTITYPOOL_HPP
#define R_TYPE_ENTITYPOOL_HPP

#include <Entity.hpp>
#include <IDrawable.hpp>
#include <vector>
#include <memory>
#include <ManagedExternalInstance.hpp>

class EntityPool {
private:
    std::vector<ManagedExternalInstance<Entity>> _pool = std::vector<ManagedExternalInstance<Entity>>();

public:
    void AddEntity(ManagedExternalInstance<Entity> &entity);
    void Draw(sf::RenderTexture &target);
};


#endif //R_TYPE_ENTITYPOOL_HPP
