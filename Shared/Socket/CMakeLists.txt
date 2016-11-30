cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_SOCKET_FILES Interfaces/IRTypeSocket.hpp Includes/RTypeNetworkPayload.h)
include_directories(Includes Interfaces)

IF (MSVC)
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Sources/RTypeSocketWindows.cpp Includes/RTypeSocketWindows.hpp)
ELSE()
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Sources/RTypeSocketLinux.cpp Includes/RTypeSocketLinux.hpp)
ENDIF()

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(LibrarySocket ${LIBRARY_SOCKET_FILES})
target_link_libraries(LibrarySocket ${CMAKE_DL_LIBS})