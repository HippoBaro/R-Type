cmake_minimum_required(VERSION 2.6.2)

project(R_Type_Client)

add_subdirectory(UnitTests)
add_subdirectory(SFML EXCLUDE_FROM_ALL)
include_directories(SYSTEM "SFML/include/")


IF (MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_SOURCE_FILES
        src/main.cpp)

add_executable(R_Type_Client ${CLIENT_SOURCE_FILES})
target_link_libraries(R_Type_Client sfml-graphics sfml-window sfml-system)
