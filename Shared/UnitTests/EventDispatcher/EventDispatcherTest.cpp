//
// Created by aguado_e on 11/25/16.
//

#include <gtest/gtest.h>
#include <EventDispatcher/EventManager.hpp>
#include <EventDispatcher/EventListener.hpp>

// Entity model
namespace RType {
    class Bullet {
    public:
        int a = 0;
    };
}

TEST(Tests_EventDispatcher, EmitEventWithSubscribeAndUnsunbscribe) {

    RType::Bullet bulletEntity;
    std::shared_ptr<RType::EventManager> e = std::shared_ptr<RType::EventManager>(new RType::EventManager);
    RType::EventListener listener(e);

    listener.Subscribe<RType::Bullet, void>(RType::BULLET_POS_CHANGE, [](RType::Bullet *bullet, void *) {
        bullet->a = 42;
    });

    e->Emit(RType::BULLET_POS_CHANGE, nullptr, &bulletEntity);
    ASSERT_EQ(bulletEntity.a, 42) << "Bullet attribute should be 42 but is  " << bulletEntity.a;

    listener.Unsubscribe(RType::BULLET_POS_CHANGE);
    bulletEntity.a = 24;
    e->Emit(RType::BULLET_POS_CHANGE, nullptr, &bulletEntity);
    ASSERT_EQ(bulletEntity.a, 24) << "Bullet attribute should be 24 but is  " << bulletEntity.a;
}