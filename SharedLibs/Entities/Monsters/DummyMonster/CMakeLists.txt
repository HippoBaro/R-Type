cmake_minimum_required(VERSION 2.6.2)
project (DrawableDummyMonster)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

include_directories(../../../../Shared/Include/Interfaces ../../../../Shared/Include ../../.. ../../../../SFML/include)

add_library(DummyMonster SHARED
        DummyMonster.hpp
        DummyMonster.cpp)

add_library(DrawableDummyMonster SHARED
        DummyMonster.hpp
        DummyMonster.cpp
        GraphicDummyMonster.cpp
        GraphicDummyMonster.hpp)
target_link_libraries(DrawableDummyMonster sfml-graphics sfml-window sfml-system)