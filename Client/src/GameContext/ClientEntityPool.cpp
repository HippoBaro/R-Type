//
// Created by hippolyteb on 11/29/16.
//

#include "ClientEntityPool.hpp"

void ClientEntityPool::Draw(sf::RenderTexture &target, TextureBag &bag) {
    for (const auto& i : _pool)
    {
        if (i->ImplementTrait(Trait::Drawable)) {
            IDrawable *entity = dynamic_cast<IDrawable*>(i.GetInstance());
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

void ClientEntityPool::AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &startTime, std::initializer_list<void *> *params) {
    auto now = startTime;
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "Drawable" + entityName, { &id, &_timer, &_eventManager, &now, &pos, params }, "createDrawable", "destroyDrawable"));
    _pool.push_back(entity);
}
