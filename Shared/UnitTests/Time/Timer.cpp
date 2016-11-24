//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>
#include <thread>
#include "../../Include/Timer.hpp"

TEST(Tests_Time, CreateTimerFromCurrentTime) {
    auto thread = new std::thread([&] {
        auto timer = Timer(std::chrono::system_clock::now());
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto now = timer.getCurrent().getMilliseconds();
        ASSERT_EQ(now.count() > 1900 || now.count() < 2100, true) << "Timer getMilliseconds() should be 2000 but is " << now.count();
    });
    thread->join();
}

TEST(Tests_Time, CreateTimerFromFutureTime) {
    auto thread = new std::thread([&] {
        auto nowClock = std::chrono::system_clock::now();
        auto dtn = std::chrono::duration<int>(std::chrono::seconds(2));
        auto future = nowClock + dtn;

        auto timer = Timer(future);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto now = timer.getCurrent().getMilliseconds();
        ASSERT_EQ(now.count() == 0, true) << "Timer getMilliseconds() should be 0 but is " << now.count();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        now = timer.getCurrent().getMilliseconds();
        ASSERT_EQ(now.count() > 1900 && now.count() < 2100, true) << "Timer getMilliseconds() should be 2000 but is " << now.count();
    });
    thread->join();
}