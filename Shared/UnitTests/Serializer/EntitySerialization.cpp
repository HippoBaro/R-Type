//
// Created by hippolyteb on 12/13/16.
//

#include <gtest/gtest.h>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include <Entities/Entity.hpp>
#include <vec2.hpp>
#include <thread>

TEST(Tests_Serialization, EntitySerialization)
{
    auto timer = std::make_shared<Timer>(std::chrono::steady_clock::now() + std::chrono::seconds(1));
    auto now = TimeRef(0);
    auto pos = vec2<float>(0, 0);
    uint16_t id = 99;
    auto eventManager = std::make_shared<RType::EventManager>();

    auto entity = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableDummyMonster", { &id, &timer , &eventManager, &now, &pos }, "create", "destroy");

    auto packer = RType::Packer(RType::WRITE);

    entity->GetInstance()->RegisterTrait(Garbage);

    std::cout << "Empty size : " << packer.getLength() << " bytes." << std::endl;
    
    entity->GetInstance()->Serialize(packer);

    std::cout << "Serialized size : " << packer.getLength() << " bytes." << std::endl;

    auto now2 = TimeRef(5000);
    auto pos2 = vec2<float>(500, 500);
    uint16_t id2 = 78;

    auto entity2 = ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DrawableDummyMonster", { &id2, &timer , &eventManager, &now2, &pos2 }, "create", "destroy");

    ASSERT_EQ(entity->GetInstance()->GetPosition().x != entity2->GetInstance()->GetPosition().x, true) << "Serialization failed";

    auto unpacker = RType::Packer(RType::READ, packer.getBuffer());
    entity2->GetInstance()->Serialize(unpacker);

    ASSERT_EQ(entity->GetInstance()->ImplementTrait(Garbage), true) << "Serialization failed";
    ASSERT_EQ(entity2->GetInstance()->ImplementTrait(Garbage), true) << "Serialization failed";
    ASSERT_EQ(entity->GetInstance()->getId() == entity2->GetInstance()->getId(), true) << "Serialization failed";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_EQ(entity->GetInstance()->GetPosition().x == entity2->GetInstance()->GetPosition().x, true) << "Serialization failed";
}