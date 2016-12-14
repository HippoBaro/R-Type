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

    ManagedExternalInstance<Entity> entity(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DummyMonster", { &id, &timer , &eventManager, &now, &pos }, "create", "destroy"));

    auto packer = RType::Packer(RType::WRITE);

    std::cout << "Empty size : " << packer.getLength() << " bytes." << std::endl;
    
    entity->Serialize(packer);

    std::cout << "Serialized size : " << packer.getLength() << " bytes." << std::endl;

    auto now2 = TimeRef(5000);
    auto pos2 = vec2<float>(500, 500);
    uint16_t id2 = 78;

    ManagedExternalInstance<Entity> entity2(ExternalClassFactoryLoader::Instance->GetInstanceOf<Entity>("", "DummyMonster", { &id2, &timer , &eventManager, &now2, &pos2 }, "create", "destroy"));

    ASSERT_EQ(entity->GetPosition().x != entity2->GetPosition().x, true) << "Serialization failed";

    auto unpacker = RType::Packer(RType::READ, packer.getBuffer());
    entity2->Serialize(unpacker);

    ASSERT_EQ(entity->getId() == entity2->getId(), true) << "Serialization failed";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_EQ(entity->GetPosition().x == entity2->GetPosition().x, true) << "Serialization failed";
}