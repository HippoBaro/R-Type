cmake_minimum_required(VERSION 2.6.2)

project(R_Type_Client)

add_subdirectory(UnitTests)
add_subdirectory(SFML EXCLUDE_FROM_ALL)
include_directories(SYSTEM "SFML/include/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused")

set(CLIENT_SOURCE_FILES
        src/main.cpp)

add_executable(R_Type_Client ${SHARED_SOURCE_FILES_ABS_G} ${CLIENT_SOURCE_FILES})
target_link_libraries(R_Type_Client sfml-graphics sfml-window sfml-system)