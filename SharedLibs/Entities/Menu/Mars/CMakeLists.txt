cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(Mars SHARED
        Mars.hpp
        Mars.cpp)
target_link_libraries(Mars)

add_library(DrawableMars SHARED
        GraphicMars.cpp
        GraphicMars.hpp
        Mars.hpp
        Mars.cpp)
target_link_libraries(DrawableMars sfml-graphics sfml-window sfml-system)
target_compile_definitions(DrawableMars PRIVATE ENTITY_DRW_CTOR=1)