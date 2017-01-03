cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(SpaceShip SHARED
        SpaceShip.hpp
        SpaceShip.cpp)
target_link_libraries(TreeResort)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableSpaceShip SHARED
            SpaceShip.hpp
            SpaceShip.cpp
            GraphicSpaceShip.cpp
            GraphicSpaceShip.hpp)
    target_link_libraries(DrawableSpaceShip sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableSpaceShip PRIVATE ENTITY_DRW_CTOR=1)
endif()