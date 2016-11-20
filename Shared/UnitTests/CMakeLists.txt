cmake_minimum_required(VERSION 3.6)

set(SHARED_TEST_FILES TestTests/Module1.cpp)

get_filename_component(SHARED_TEST_FILES_ABS ${SHARED_TEST_FILES} REALPATH)
set(SHARED_TEST_FILES_ABS_G ${SHARED_TEST_FILES_ABS} CACHE INTERNAL "")

add_executable(SharedUnitTests ../../UnitTests/gtest.cpp ${SHARED_TEST_FILES})
target_link_libraries(SharedUnitTests gtest)