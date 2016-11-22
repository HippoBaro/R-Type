cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(SHARED_SOURCE_FILES src/main.cpp)

include_directories(Libs/Interfaces)

get_filename_component(SHARED_SOURCE_FILES_ABS ${SHARED_SOURCE_FILES} REALPATH)
set(SHARED_SOURCE_FILES_ABS_G ${SHARED_SOURCE_FILES_ABS} CACHE INTERNAL "")