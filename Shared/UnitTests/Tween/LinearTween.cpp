//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>
#include <thread>
#include "../../Include/Tween.hpp"
#include "../../Include/LinearCurve.hpp"

TEST(Tests_LinearTween, CreateTweenStartingFromCurrentTime) {
    auto timer = std::make_shared<Timer>(std::chrono::system_clock::now());

    Tween<int, LinearCurve> tween(timer, 0, timer->getStart(), 100, timer->getCurrent().GetRelative(std::chrono::milliseconds(1000)));
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    int now = tween.GetTweened();
    ASSERT_EQ(now > 23 && now < 27, true) << "Tween should be 50 but is " << now;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    now = tween.GetTweened();
    ASSERT_EQ(now > 73 && now < 77, true) << "Tween should be 50 but is " << now;
}

TEST(Tests_LinearTween, CreateTweenStartingFromFutureTime) {
    auto nowClock = std::chrono::system_clock::now();
    auto dtn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(500));
    auto future = nowClock + dtn;

    auto timer = std::make_shared<Timer>(future);

    Tween<int, LinearCurve> tween(timer, 0, timer->getStart(), 100, timer->getStart().GetRelative(std::chrono::milliseconds(1000)));
    std::this_thread::sleep_for(std::chrono::milliseconds(490));
    int now = tween.GetTweened();
    ASSERT_EQ(now == 0, true) << "Tween should be 0 but is " << now;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    now = tween.GetTweened();
    ASSERT_EQ(now > 47 && now < 53, true) << "Tween should be 50 but is " << now;

    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    now = tween.GetTweened();
    ASSERT_EQ(now == 100, true) << "Tween should be 100 but is " << now;
}