//
// Created by hippolyteb on 11/28/16.
//

#include <vec2.hpp>
#include "EntityPool.hpp"
#include "../../Client/SFML/include/SFML/Graphics/RenderTarget.hpp"
#include "../../Client/SFML/include/SFML/Graphics/RenderTexture.hpp"

void EntityPool::AddEntity(Entity *entity) {
    _pool.push_back(std::unique_ptr<Entity>(entity));
}

void EntityPool::Draw(sf::RenderTexture &target) {
    for (const auto& i : _pool)
    {
        if (i->ImplementTrait(Trait::Drawable)){
            IDrawable *drawable = (IDrawable *)i.get();

            sf::RenderTexture frame;
            frame.create(drawable->GetRenderRect().x, drawable->GetRenderRect().y);
            frame.clear();
            drawable->Draw(frame);
            frame.display();
            sf::Sprite sprite;
            sprite.setTexture(frame.getTexture());
            sprite.setPosition(drawable->GetPosition().x, drawable->GetPosition().y);
            target.draw(sprite);
        }
    }
    target.display();
}
