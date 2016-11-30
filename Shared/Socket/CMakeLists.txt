cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_SOCKET_FILES Interfaces/IRTypeSocket.hpp Includes/RTypeNetworkPayload.h)
include_directories(Includes Interfaces)

IF (MSVC)
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Windows/RTypeSocket.cpp Windows/RTypeSocket.hpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(LIB_SOCKET ws2_32)
ELSE()
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Linux/RTypeSocket.cpp Linux/RTypeSocket.hpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(LibrarySocket STATIC ${LIBRARY_SOCKET_FILES})
target_link_libraries(LibrarySocket ${LIB_SOCKET})