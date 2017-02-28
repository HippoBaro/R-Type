//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>
#include <thread>
#include <Time/Timer.hpp>

TEST(Tests_TimeRef, AddTimeRef) {
    auto timer = Timer(std::chrono::steady_clock::now());
    auto now = timer.getCurrent();
    auto future = now.GetRelative(std::chrono::seconds(10));
    ASSERT_EQ(future.getMilliseconds().count() >= 10000 && future.getMilliseconds().count() < 10100, true) << "TimeRef getMilliseconds() should be 10000 but is " << future.getMilliseconds().count();
}

TEST(Tests_TimeRef, SubstractTimeRef) {
    auto now = TimeRef(std::chrono::seconds(10));
    auto past = now.GetRelative(std::chrono::seconds(-10));
    ASSERT_EQ(past.getMilliseconds().count() >= 0 && past.getMilliseconds().count() < 100, true) << "TimeRef getMilliseconds() should be 0 but is " << past.getMilliseconds().count();
}

TEST(Tests_TimeRef, CompareTimeRef) {
    auto now = TimeRef(std::chrono::seconds(10));
    auto past = now.GetRelative(std::chrono::seconds(-10));
    ASSERT_EQ(now > past, true) << "now should be > to past";
    auto now2 = past.GetRelative(std::chrono::seconds(10));
    ASSERT_EQ(now2 == now, true) << "now2 should be == to now";
}