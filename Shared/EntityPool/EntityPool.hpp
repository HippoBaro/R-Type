//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_ENTITYPOOL_HPP
#define R_TYPE_ENTITYPOOL_HPP


#include <Entity.hpp>
#include <IDrawable.hpp>
#include <vector>
#include <bits/unique_ptr.h>

class EntityPool {
private:
    std::vector<std::unique_ptr<Entity>> _pool = std::vector<std::unique_ptr<Entity>>();

public:
    void AddEntity(Entity *entity);
    void Draw();
};


#endif //R_TYPE_ENTITYPOOL_HPP
