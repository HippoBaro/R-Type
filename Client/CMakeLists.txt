cmake_minimum_required(VERSION 3.6)
project(R_Type_Client)

add_subdirectory(UnitTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_SOURCE_FILES src/main.cpp)

add_executable(R_Type_Client ${CLIENT_SOURCE_FILES})