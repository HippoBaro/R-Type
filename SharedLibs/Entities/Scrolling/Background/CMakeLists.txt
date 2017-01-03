cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(Background SHARED
        Background.hpp
        Background.cpp)
target_link_libraries(Background)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableBackground SHARED
            Background.hpp
            Background.cpp
            GraphicBackground.cpp
            GraphicBackground.hpp)
    target_link_libraries(DrawableBackground sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableBackground PRIVATE ENTITY_DRW_CTOR=1)
endif()