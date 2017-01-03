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

private:
    std::shared_ptr<RType::EventManager> _globalEventManager;
    std::unique_ptr<RType::EventListener> _globalEventListener;
    std::shared_ptr<ManagedExternalInstance<Entity>> _backgroundEntity = nullptr;

public:
    ClientEntityPool(const std::shared_ptr<Timer> &, const std::shared_ptr<RType::EventManager> &eventManager);

public :
    virtual void Draw(sf::RenderTexture &, TextureBag &);

    virtual void AddEntity(std::string const &entityName, uint16_t, vec2<float> const &initialPos, TimeRef const &, std::initializer_list<void *> * = nullptr) override;

    void AddEntity(const std::shared_ptr<ManagedExternalInstance<Entity>> &instance) override;

    void RegisterType(std::string const &string) override;

    void LoadPartition(std::string const &string) override;

    void CleanBasedOnServer(std::set<uint16_t> &ids);

    virtual void SetBackground(std::string const &entityName, uint16_t, vec2<float> const &initialPos, TimeRef const &, std::initializer_list<void *> * = nullptr);


protected:
    virtual void SpawnProjectile(const FireProjectileMessage &message, const uint16_t emitterId) override;

private:
    void DrawBackground(sf::RenderTexture &target, TextureBag &bag);
};


#endif //R_TYPE_CLIENTENTITYPOOL_HPP
