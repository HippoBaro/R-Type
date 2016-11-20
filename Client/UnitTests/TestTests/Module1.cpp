//
// Created by pasteu_e on 11/20/16.
//

#include <gtest/gtest.h>

TEST(Client_Test_Module1, CanBindToValidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "Should be equal to two !";
}

TEST(Client_Test_Module1, CanBindToInvalidEndpoint) {
    ASSERT_EQ(1 * 2, 23) << "This will fail !";
}