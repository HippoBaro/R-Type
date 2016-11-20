cmake_minimum_required(VERSION 2.6.2)

set(SERVER_TEST_FILES TestTests/Module1.cpp)

get_filename_component(SERVER_TEST_FILES_ABS ${SERVER_TEST_FILES} REALPATH)
set(SERVER_TEST_FILES_ABS_G ${SERVER_TEST_FILES_ABS} CACHE INTERNAL "")

add_executable(ServerUnitTests ../../UnitTests/gtest.cpp ${SERVER_TEST_FILES})
target_link_libraries(ServerUnitTests gtest)