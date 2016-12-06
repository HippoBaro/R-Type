cmake_minimum_required(VERSION 2.6.2)
project (DrawableSimpleProjectile)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

include_directories(../../../../Shared/Libs/Interfaces ../../../../Shared/Include ../../.. ../../../../SFML/include)

add_library(SimpleProjectile SHARED
        SimpleProjectile.hpp
        SimpleProjectile.cpp)

add_library(DrawableSimpleProjectile SHARED
        SimpleProjectile.cpp
        SimpleProjectile.hpp
        DrawableSimpleProjectile.cpp
        DrawableSimpleProjectile.hpp)
target_link_libraries(DrawableSimpleProjectile sfml-graphics sfml-window sfml-system)