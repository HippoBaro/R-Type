cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(OrbMonster SHARED
        OrbMonster.hpp
        OrbMonster.cpp)
target_link_libraries(OrbMonster)

add_library(DrawableOrbMonster SHARED
        OrbMonster.hpp
        OrbMonster.cpp
        GraphicOrbMonster.cpp
        GraphicOrbMonster.hpp)
target_link_libraries(DrawableOrbMonster sfml-graphics sfml-window sfml-system)
target_compile_definitions(DrawableOrbMonster PRIVATE ENTITY_DRW_CTOR=1)
