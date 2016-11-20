cmake_minimum_required(VERSION 3.6)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests gtest.cpp testAssert.cpp)

target_link_libraries(runUnitTests gtest)