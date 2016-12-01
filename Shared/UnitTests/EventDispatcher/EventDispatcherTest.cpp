//
// Created by aguado_e on 11/25/16.
//

#include <gtest/gtest.h>
#include <EventDispatcher/EventManager.hpp>
#include <EventDispatcher/EventListener.hpp>


// Entity model
namespace RType {

  class IEntity {
  public:
    IEntity() {}
    int a = 0;
  };
  class Bullet : public IEntity {
  public:
    Bullet() : IEntity() {}
  };
}

TEST(Tests_EventDispatcher, EmitEventWithSubscribeAndUnsunbscribe) {

  RType::Bullet bulletEntity;
  std::shared_ptr<RType::EventManager> e = std::shared_ptr<RType::EventManager>(new RType::EventManager);
  RType::EventListener<RType::Bullet> listener(e);

  listener.Subscribe(RType::BULLET_POS_CHANGE, [](RType::Bullet &bullet) {
    bullet.a = 42;
  });

  e->Emit(RType::BULLET_POS_CHANGE, bulletEntity);
  ASSERT_EQ(bulletEntity.a, 42) << "Bullet attribute should be 42 but is  " << bulletEntity.a;

  listener.Unsubscribe(RType::BULLET_POS_CHANGE);
  bulletEntity.a = 24;
  e->Emit(RType::BULLET_POS_CHANGE, bulletEntity);
  ASSERT_EQ(bulletEntity.a, 24) << "Bullet attribute should be 24 but is  " << bulletEntity.a;
}