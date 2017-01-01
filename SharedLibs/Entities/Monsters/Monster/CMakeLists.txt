cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(TreeResort SHARED
        TreeResort.hpp
        TreeResort.cpp)
target_link_libraries(TreeResort)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableTreeResort SHARED
            TreeResort.hpp
            TreeResort.cpp
            GraphicTreeResort.cpp
            GraphicTreeResort.hpp)
    target_link_libraries(DrawableTreeResort sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableTreeResort PRIVATE ENTITY_DRW_CTOR=1)
endif()