cmake_minimum_required(VERSION 3.6)
project(R_Type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(UnitTests)

set(SOURCE_FILES src/main.cpp)

add_executable(R_Type ${SOURCE_FILES})