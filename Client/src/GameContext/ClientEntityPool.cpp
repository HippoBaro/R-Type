//
// Created by hippolyteb on 11/29/16.
//

#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "ClientEntityPool.hpp"

void ClientEntityPool::Draw(sf::RenderTexture &target, TextureBag &bag) {
    for (const auto& i : _pool)
    {
        if (i->ImplementTrait(Trait::Drawable)) {
            IDrawable *entity = dynamic_cast<IDrawable*>(i.GetInstance());
            auto renderTarget = entity->getRenderTexture();
            if (renderTarget == nullptr)
                renderTarget = entity->createRenderTexture((unsigned int) i->GetRenderRect().x, (unsigned int) i->GetRenderRect().y);
            entity->Draw(renderTarget, bag);
            renderTarget->display();
            sf::Sprite sprite;
            sprite.setTexture(renderTarget->getTexture());
            sprite.setPosition(i->GetPosition().x, i->GetPosition().y);
            target.draw(sprite);
        }
    }
}

void ClientEntityPool::AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &startTime, std::initializer_list<void *> *params) {
    auto now = startTime;
    auto pos = initialPos;
    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "Drawable" + entityName, { &id, &_timer, &_eventManager, &now, &pos, params }, "createDrawable", "destroyDrawable"));
    _factory.RegisterEntityType(entity->getTypeId(), "Drawable" + entityName);
    _pool.push_back(entity);
}

ClientEntityPool::ClientEntityPool(const std::shared_ptr<Timer> &timer,
                                   const std::shared_ptr<RType::EventManager> &eventManager) : EntityPool(timer),
                                                                                               _globalEventManager(eventManager),
                                                                                               _globalEventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager))) {

    _globalEventListener->Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {

    });
}
