//
// Created by hippolyteb on 11/29/16.
//

#include <Entities/DrawableEntity.hpp>
#include "ClientEntityPool.hpp"

void ClientEntityPool::Draw(sf::RenderTexture &target, TextureBag &bag) {
    for (const auto& i : _pool)
    {
        Trait traitDrawable = Drawable;
        DrawableEntity *entity = dynamic_cast<DrawableEntity*>(i.GetInstance());
        if (entity->ImplementTrait(traitDrawable)) {
            auto renderTarget = entity->getRenderTexture();
            if (renderTarget == nullptr)
                renderTarget = entity->createRenderTexture((unsigned int) entity->GetRenderRect().x, (unsigned int) entity->GetRenderRect().y);
            entity->Draw(renderTarget, bag);
            renderTarget->display();
            sf::Sprite sprite;
            sprite.setTexture(renderTarget->getTexture());
            sprite.setPosition(entity->GetPosition().x, entity->GetPosition().y);
            target.draw(sprite);
        }
    }
}

ClientEntityPool::ClientEntityPool(const std::shared_ptr<Timer> &timer) : EntityPool(timer) {}

void ClientEntityPool::AddEntity(std::string const &entityName, vec2<float> const &initialPos) {
    auto now = _timer->getCurrent();
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "Drawable" + entityName, {_timer.get() , _eventManager.get(), &now, &pos }, "createDrawable", "destroyDrawable"));
    _pool.push_back(entity);
}
