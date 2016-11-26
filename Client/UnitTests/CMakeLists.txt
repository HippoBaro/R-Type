cmake_minimum_required(VERSION 2.6.2)

set(CLIENT_TEST_FILES TestTests/Module1.cpp)

foreach (_file ${CLIENT_TEST_FILES})
    get_filename_component(CLIENT_TEST_FILES_ABS ${_file} REALPATH)
    set(CLIENT_TEST_FILES_ABS_G ${CLIENT_TEST_FILES_ABS_G} ${CLIENT_TEST_FILES_ABS} CACHE INTERNAL "")
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ClientUnitTests ../../UnitTests/gtest.cpp ${CLIENT_TEST_FILES})
target_link_libraries(ClientUnitTests gtest)
