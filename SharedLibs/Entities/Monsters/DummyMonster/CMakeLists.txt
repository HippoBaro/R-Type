cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(DummyMonster SHARED
        DummyMonster.hpp
        DummyMonster.cpp)
target_link_libraries(DummyMonster)

add_library(DrawableDummyMonster SHARED
        GraphicDummyMonster.cpp
        GraphicDummyMonster.hpp
        DummyMonster.hpp
        DummyMonster.cpp)
target_link_libraries(DrawableDummyMonster sfml-graphics sfml-window sfml-system)
target_compile_definitions(DrawableDummyMonster PRIVATE ENTITY_DRW_CTOR=1)