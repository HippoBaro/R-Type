cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_TEST_FILES Time/Timer.cpp Time/TimeRef.cpp Tween/LinearTween.cpp PartitionSystem/EntityPartition.cpp EventDispatcher/EventDispatcherTest.cpp Socket/SocketTest.cpp)

include_directories(../Include ../Socket/Includes ../Socket/Interfaces)
foreach (_file ${SHARED_TEST_FILES})
    get_filename_component(SHARED_TEST_FILES_ABS ${_file} REALPATH)
    set(SHARED_TEST_FILES_ABS_G ${SHARED_TEST_FILES_ABS_G} ${SHARED_TEST_FILES_ABS} CACHE INTERNAL "")
endforeach()

add_executable(SharedUnitTests ../../UnitTests/gtest.cpp ${SHARED_TEST_FILES})
target_link_libraries(SharedUnitTests gtest RTypeShared)