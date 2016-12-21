cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(Player SHARED
        Player.hpp
        Player.cpp ../../Interfaces/IUserControlled.hpp)

add_library(DrawablePlayer SHARED
        GraphicPlayer.cpp
        GraphicPlayer.hpp
        Player.hpp
        Player.cpp)
target_link_libraries(DrawablePlayer sfml-graphics sfml-window sfml-system)
target_compile_definitions(DrawablePlayer PRIVATE ENTITY_DRW_CTOR=1)
