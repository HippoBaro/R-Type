cmake_minimum_required(VERSION 2.6.2)

set(SERVER_TEST_FILES ./TestTests/Module1.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

foreach (_file ${SERVER_TEST_FILES})
    get_filename_component(SERVER_TEST_FILE_ABS ${_file} REALPATH)
    set(SERVER_TEST_FILES_ABS_G ${SERVER_TEST_FILES_ABS_G} ${SERVER_TEST_FILE_ABS} CACHE INTERNAL "")
endforeach()

add_executable(ServerUnitTests ../../UnitTests/gtest.cpp ${SERVER_TEST_FILES})
target_link_libraries(ServerUnitTests gtest)
