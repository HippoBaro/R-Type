cmake_minimum_required(VERSION 2.6.2)
project(R_Type_Server)

find_package(Threads)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(UnitTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE_FILES
        main.cpp

        GameInstance/GameInstanceManager.cpp
        GameInstance/GameInstance.cpp
        GameManager/GameManager.cpp
        NetworkManager/NetworkManager.cpp
        LobbyManager/LobbyManager.cpp
        LobbyInstance/LobbyInstance.cpp

        Include/GameInstance/GameInstanceManager.hpp
        Include/GameInstance/GameInstance.hpp
        Include/GameManager/GameManager.hpp
        Include/NetworkManager/NetworkManager.hpp
        Include/LobbyManager/LobbyManager.hpp
        Include/LobbyInstance/LobbyInstance.hpp
        )

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter -Wno-unused-private-field")
ENDIF()

add_executable(R_Type_Server ${SERVER_SOURCE_FILES})
target_link_libraries(R_Type_Server RTypeShared ${CMAKE_THREAD_LIBS_INIT})
