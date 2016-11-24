cmake_minimum_required(VERSION 2.6.2)
project(R_Type_Server)

include_directories(../Shared/LibraryLoader/ ../Shared/Libs/Interfaces ../Shared/Include)
add_subdirectory(UnitTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE_FILES src/main.cpp)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_executable(R_Type_Server ${SERVER_SOURCE_FILES})

target_link_libraries(R_Type_Server RTypeShared)