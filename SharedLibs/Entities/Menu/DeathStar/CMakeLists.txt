cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(DeathStar SHARED
        DeathStar.hpp
        DeathStar.cpp)
target_link_libraries(DeathStar)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableDeathStar SHARED
            GraphicDeathStar.cpp
            GraphicDeathStar.hpp
            DeathStar.hpp
            DeathStar.cpp)
    target_link_libraries(DrawableDeathStar sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableDeathStar PRIVATE ENTITY_DRW_CTOR=1)
endif()