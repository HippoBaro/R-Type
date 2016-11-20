cmake_minimum_required(VERSION 3.6)

set(CLIENT_TEST_FILES TestTests/Module1.cpp)

get_filename_component(CLIENT_TEST_FILES_ABS ${CLIENT_TEST_FILES} REALPATH)
set(CLIENT_TEST_FILES_ABS_G ${CLIENT_TEST_FILES_ABS} CACHE INTERNAL "")

add_executable(ClientUnitTests ../../UnitTests/gtest.cpp ${CLIENT_TEST_FILES})
target_link_libraries(ClientUnitTests gtest)