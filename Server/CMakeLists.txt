cmake_minimum_required(VERSION 2.6.2)
project(R_Type_Server)

add_subdirectory(UnitTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE_FILES src/main.cpp)

add_executable(R_Type_Server ${SERVER_SOURCE_FILES})