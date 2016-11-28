//
// Created by hippolyteb on 11/28/16.
//

#include <vec2.hpp>
#include <DrawableEntity.hpp>
#include <iostream>
#include "EntityPool.hpp"
#include "../LibraryLoader/ManagedExternalInstance.hpp"

void EntityPool::AddEntity(ManagedExternalInstance<Entity> &entity) {
    _pool.push_back(entity);
}

void EntityPool::Draw(sf::RenderTexture &target) {
    for (const auto& i : _pool)
    {
        Trait traitDrawable = Drawable;
        DrawableEntity *entity = dynamic_cast<DrawableEntity*>(i.operator->());
        if (entity->ImplementTrait(traitDrawable)) {
            sf::RenderTexture frame;
            frame.create((unsigned int) entity->GetRenderRect().x, (unsigned int) entity->GetRenderRect().y);
            //frame.clear();
            entity->Draw(frame);
            frame.display();
            sf::Sprite sprite;
            sprite.setTexture(frame.getTexture());
            sprite.setPosition(entity->GetPosition().x, entity->GetPosition().y);
            target.draw(sprite);
        }
    }
}