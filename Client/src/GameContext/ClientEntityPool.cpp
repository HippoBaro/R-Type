//
// Created by hippolyteb on 11/29/16.
//

#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <Json/Json.hpp>
#include "ClientEntityPool.hpp"

void ClientEntityPool::Draw(sf::RenderTexture &target, TextureBag &bag) {
    for (const auto& i : _pool)
    {
        if (i.second->GetInstance()->ImplementTrait(Trait::Drawable)) {
            IDrawable *entity = dynamic_cast<IDrawable*>(i.second->GetInstance());
            auto renderTarget = entity->getRenderTexture();
            auto sprite = entity->getSprite();
            if (sprite == nullptr)
                sprite = entity->createSprite();
            if (renderTarget == nullptr || entity->NeedRedraw())
            {
                if (renderTarget == nullptr)
                    renderTarget = entity->createRenderTexture((unsigned int) i.second->GetInstance()->GetRenderRect().x, (unsigned int) i.second->GetInstance()->GetRenderRect().y);
                entity->Draw(renderTarget, bag);
                renderTarget->display();
                sprite->setTexture(renderTarget->getTexture());
            }
			auto currentPos = i.second->GetInstance()->GetPosition();
            sprite->setPosition(currentPos.x, currentPos.y);

            target.draw(*sprite);
        }
    }
}

void ClientEntityPool::AddEntity(std::string const &entityName, uint16_t id, vec2<float> const &initialPos, TimeRef const &startTime, std::initializer_list<void *> *params) {
    auto now = startTime;
    auto pos = initialPos;
    auto entity = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "Drawable" + entityName, { &id, &_timer, &_eventManager, &now, &pos, params }, "create", "destroy");
    EntityPool::AddEntity(entity);
}

ClientEntityPool::ClientEntityPool(const std::shared_ptr<Timer> &timer,
                                   const std::shared_ptr<RType::EventManager> &eventManager) : EntityPool(timer),
                                                                                               _globalEventManager(eventManager),
                                                                                               _globalEventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager))) {

}

void ClientEntityPool::AddEntity(const std::shared_ptr<ManagedExternalInstance<Entity>> &instance) {
    EntityPool::AddEntity(instance);
}

void ClientEntityPool::RegisterType(std::string const &string) {
    EntityPool::RegisterType("Drawable" + string);
}

void ClientEntityPool::LoadPartition(std::string const &partition) {
    RType::json j;

    j = RType::json::parse(partition);
    for (auto const &i : j["entityTypes"])
        RegisterType(i);

    if (!j["backgroundEntity"].is_null()) {
        std::string name = j["backgroundEntity"]["entityName"];
        vec2<float> startPos(j["backgroundEntity"]["startPosition"]["x"], j["backgroundEntity"]["startPosition"]["y"]);
        TimeRef startTime((std::chrono::milliseconds(j["backgroundEntity"]["startTime"])));
        uint16_t id = j["backgroundEntity"]["id"];
        AddEntity(name, id, startPos, startTime);
    }
}

void ClientEntityPool::SpawnProjectile(const FireProjectileMessage &message, const uint16_t emitterId) {
    //EntityPool::SpawnProjectile(message, emitterId);
}

void ClientEntityPool::CleanBasedOnServer(std::set<uint16_t> &ids) {
    for (auto &entity : _pool) {
        if (ids.count(entity.first) == 0)
            entity.second->GetInstance()->RegisterTrait(Trait::Garbage); //Detroy
    }
}
