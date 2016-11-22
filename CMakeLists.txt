cmake_minimum_required(VERSION 2.6.2)
project(R_Type)

include(cmake/ucm.cmake)

if(MSVC)
    add_definitions(-DMSVC)
endif()

add_subdirectory(SharedLibs)
add_subdirectory(Shared)
add_subdirectory(Client)
add_subdirectory(Server)

ucm_set_runtime(STATIC)

add_subdirectory(UnitTests)