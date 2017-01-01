cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

include_directories(../../../../Shared/Libs/Interfaces ../../../../Shared/Include ../../.. ../../../../SFML/include)

add_library(SimpleProjectile SHARED
        SimpleProjectile.hpp
        SimpleProjectile.cpp)
target_link_libraries(SimpleProjectile)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableSimpleProjectile SHARED
            DrawableSimpleProjectile.cpp
            DrawableSimpleProjectile.hpp
            SimpleProjectile.cpp
            SimpleProjectile.hpp)
    target_link_libraries(DrawableSimpleProjectile sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableSimpleProjectile PRIVATE ENTITY_DRW_CTOR=1)
endif()