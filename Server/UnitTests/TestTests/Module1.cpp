//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>


TEST(Server_Test_Module1, CanBindToValidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "Should be equal to two !";
}

TEST(Server_Test_Module1, CanBindToInvalidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "This will fail !";
}