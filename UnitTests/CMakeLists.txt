cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(AllUnitTests gtest.cpp ${CLIENT_TEST_FILES_ABS_G} ${SERVER_TEST_FILES_ABS_G} ${SHARED_TEST_FILES_ABS_G})
#target_link_libraries(AllUnitTests gtest RTypeShared)