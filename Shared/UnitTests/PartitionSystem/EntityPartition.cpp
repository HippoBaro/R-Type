//
// Created by hippolyteb on 11/26/16.
//

#include <gtest/gtest.h>
#include <thread>
#include <EntityPartitionBuilder.hpp>

TEST(EntityPartionTest, PlayPlayValidEntityPartition) {
    auto timer = new Timer(std::chrono::system_clock::now());

    //Create our entity partition
    auto partition = EntityPartitionBuilder(timer, vec2<float>(0, 0))
            .AddSegment(PartitionSegmentBuilder()
                                .Begins(timer->getCurrent())
                                .For(std::chrono::seconds(1))
                                .Translate(vec2<float>(20, 20)))
            .AddSegment(PartitionSegmentBuilder()
                                  .For(std::chrono::milliseconds(500))
                                  .Translate(vec2<float>(-15, -15)))
            .Loop(2)
            .Build();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 10.2 && current.x >= 9.8 &&
              current.y <= 10.2 && current.y >= 9.8, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 20 && current.x >= 19.8 &&
              current.y <= 20 && current.y >= 19.8, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 13.2 && current.x >= 12.3 &&
              current.y <= 13.2 && current.y >= 12.3, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 5.2 && current.x >= 4.8 &&
              current.y <= 5.2 && current.y >= 4.8, true) << "Partition wasn't played correctly. Vec was :" << current.x;
}