cmake_minimum_required(VERSION 2.6.2)
project(R_Type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(Shared)
add_subdirectory(Client)
add_subdirectory(Server)

add_subdirectory(UnitTests)