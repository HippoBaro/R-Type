cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SHARED_SOURCE_FILES src/main.cpp Time/TimeRef.cpp Time/TimeRef.hpp Time/Timer.cpp Time/Timer.hpp)

include_directories(Libs/Interfaces)

add_library(RTypeShared ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)