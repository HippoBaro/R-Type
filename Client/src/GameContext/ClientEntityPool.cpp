//
// Created by hippolyteb on 11/29/16.
//

#include <Entities/DrawableEntity.hpp>
#include "ClientEntityPool.hpp"

void ClientEntityPool::Draw(sf::RenderTexture &target) {
    for (const auto& i : _pool)
    {
        Trait traitDrawable = Drawable;
        DrawableEntity *entity = dynamic_cast<DrawableEntity*>(i.GetInstance());
        if (entity->ImplementTrait(traitDrawable)) {
            sf::RenderTexture frame;
            frame.create((unsigned int) entity->GetRenderRect().x, (unsigned int) entity->GetRenderRect().y);
            entity->Draw(frame);
            frame.display();
            sf::Sprite sprite;
            sprite.setTexture(frame.getTexture());
            sprite.setPosition(entity->GetPosition().x, entity->GetPosition().y);
            target.draw(sprite);
        }
    }
}