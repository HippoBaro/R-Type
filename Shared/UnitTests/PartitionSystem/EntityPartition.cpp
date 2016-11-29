//
// Created by hippolyteb on 11/26/16.
//

#include <gtest/gtest.h>
#include <thread>
#include <EntityPartitionBuilder.hpp>

TEST(EntityPartionTest, PlayPlayValidEntityPartition) {
    auto timer = new Timer(std::chrono::system_clock::now());

    //Create our entity partition
    auto partition = EntityPartitionBuilder(timer)
            .AddSegment(PartitionSegmentBuilder()
                                .Begins(timer->getCurrent())
                                .For(std::chrono::seconds(1))
                                .From(vec2<int>(0, 0))
                                .To(vec2<int>(20, 20)))
            .ContinueWith(PartitionSegmentBuilder()
                                  .For(std::chrono::milliseconds(500))
                                  .To(vec2<int>(5, 5)))
            .Loop(2)
            .Build();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 10.1 && current.x >= 9.9 &&
              current.y <= 10.1 && current.y >= 9.9, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 20 && current.x >= 19.9 &&
              current.y <= 20 && current.y >= 19.9, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 13.1 && current.x >= 12.4 &&
              current.y <= 13.1 && current.y >= 12.4, true) << "Partition wasn't played correctly. Vec was :" << current.x;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    current = partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
    ASSERT_EQ(current.x <= 5.1 && current.x >= 4.9 &&
              current.y <= 5.1 && current.y >= 4.9, true) << "Partition wasn't played correctly. Vec was :" << current.x;
}