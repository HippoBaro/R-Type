cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(TentacleBoss SHARED
        TentacleBoss.hpp
        TentacleBoss.cpp)
target_link_libraries(TentacleBoss)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_library(DrawableTentacleBoss SHARED
            TentacleBoss.hpp
            TentacleBoss.cpp
            GraphicTentacleBoss.cpp
            GraphicTentacleBoss.hpp)
    target_link_libraries(DrawableTentacleBoss sfml-graphics sfml-window sfml-system)
    target_compile_definitions(DrawableTentacleBoss PRIVATE ENTITY_DRW_CTOR=1)
endif()