cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

include_directories(../../../../Shared/Libs/Interfaces ../../../../Shared/Include ../../.. ../../../../SFML/include)

add_library(BigProjectile SHARED
        BigProjectile.hpp
        BigProjectile.cpp)
target_link_libraries(BigProjectile)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableBigProjectile SHARED
            DrawableBigProjectile.cpp
            DrawableBigProjectile.hpp
            BigProjectile.cpp
            BigProjectile.hpp)
    target_link_libraries(DrawableBigProjectile sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableBigProjectile PRIVATE ENTITY_DRW_CTOR=1)
endif()