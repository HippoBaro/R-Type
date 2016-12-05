cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_TEST_FILES Time/Timer.cpp Time/TimeRef.cpp Tween/LinearTween.cpp PartitionSystem/EntityPartition.cpp EventDispatcher/EventDispatcherTest.cpp Socket/SocketTest.cpp)

IF (MSVC)
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Socket/Windows)
ELSE()
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Socket/Linux)
ENDIF()

include_directories(../Include ../Socket/Includes ../Socket/Interfaces ../Socket/Enum ${LIBRARY_SOCKET_HEADER_FOLDER})

foreach (_file ${SHARED_TEST_FILES})
    get_filename_component(SHARED_TEST_FILES_ABS ${_file} REALPATH)
    set(SHARED_TEST_FILES_ABS_G ${SHARED_TEST_FILES_ABS_G} ${SHARED_TEST_FILES_ABS} CACHE INTERNAL "")

    get_filename_component(TEST_SRC ${_file} NAME_WE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(TEST_SRC_PRE "UnitTestShared${TEST_SRC}")
    add_executable(${TEST_SRC_PRE} ../../UnitTests/gtest.cpp ${_file})
    target_link_libraries(${TEST_SRC_PRE} gtest RTypeShared)

    set(TEST_SRC "Shared_${TEST_SRC}")
    add_test(NAME ${TEST_SRC} COMMAND $<TARGET_FILE:${TEST_SRC_PRE}>)
endforeach()

add_executable(SharedUnitTests ../../UnitTests/gtest.cpp ${SHARED_TEST_FILES})
target_link_libraries(SharedUnitTests gtest RTypeShared)