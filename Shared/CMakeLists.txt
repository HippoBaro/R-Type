cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(SHARED_SOURCE_FILES src/main.cpp)

include_directories(Libs/Interfaces)

add_library(RTypeShared ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)