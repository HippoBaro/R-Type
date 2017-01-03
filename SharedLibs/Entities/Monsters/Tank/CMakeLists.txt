cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(Tank SHARED
        Tank.hpp
        Tank.cpp)
target_link_libraries(Tank)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableTank SHARED
            Tank.hpp
            Tank.cpp
            GraphicTank.cpp
            GraphicTank.hpp)
    target_link_libraries(DrawableTank sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableTank PRIVATE ENTITY_DRW_CTOR=1)
endif()