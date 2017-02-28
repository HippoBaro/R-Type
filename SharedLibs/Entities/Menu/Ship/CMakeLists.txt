cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(Ship SHARED
        Ship.hpp
        Ship.cpp)
target_link_libraries(Ship)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableShip SHARED
            GraphicShip.cpp
            GraphicShip.hpp
            Ship.hpp
            Ship.cpp)
    target_link_libraries(DrawableShip sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableShip PRIVATE ENTITY_DRW_CTOR=1)
endif()