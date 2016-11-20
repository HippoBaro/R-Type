//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>


TEST(Tests_Socket_UDP, CanBindToValidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "Should be equal to two !";
}

TEST(Tests_Socket_UDP, CanBindToInvalidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "This will fail !";
}