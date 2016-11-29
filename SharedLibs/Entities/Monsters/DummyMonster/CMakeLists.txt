cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

include_directories(../../../../Shared/Libs/Interfaces ../../../../Shared/Include ../../.. ../../../../Client/SFML/include)

set(SOURCES DummyMonster.hpp DummyMonster.cpp)

if (GRAPHICCLIENT)
    set(SOURCES ${SOURCES} )
endif()

add_library(DummyMonster SHARED ${SOURCES})
link_libraries(DummyMonster RTypeShared pthread)

add_library(DrawableDummyMonster SHARED GraphicDummyMonster.cpp GraphicDummyMonster.hpp)
link_libraries(DrawableDummyMonster DummyMonster)