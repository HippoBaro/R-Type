cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(Player SHARED
        Player.hpp
        Player.cpp)

add_library(DrawablePlayer SHARED
        Player.hpp
        Player.cpp
        GraphicPlayer.cpp
        GraphicPlayer.hpp)
target_link_libraries(DrawablePlayer sfml-graphics sfml-window sfml-system)