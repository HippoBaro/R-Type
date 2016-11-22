cmake_minimum_required(VERSION 2.6.2)

IF (MSVC)
    add_definitions(-DWIN32)
ENDIF()

add_subdirectory(Test)