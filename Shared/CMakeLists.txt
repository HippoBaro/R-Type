cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(SHARED_SOURCE_FILES
        src/main.cpp
        EventDispatcher/EventManager.cpp
        EntityPool/EntityPool.cpp)

include_directories(Libs/Interfaces ../SFML/include LibraryLoader Socket/ Socket/Interfaces Socket/Enum ../SharedLibs/Interfaces)

IF (MSVC)
    set(LIBRARY_SOCKET_FILES Socket/Windows/RTypeSocket.hpp)
    set(LIB_SOCKET ws2_32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_SOCKET_FILES Socket/Linux/RTypeSocket.hpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared STATIC ${SHARED_SOURCE_FILES} ${LIBRARY_SOCKET_FILES})
target_link_libraries(RTypeShared LibraryLoader ${LIB_SOCKET})