cmake_minimum_required(VERSION 2.6.2)
project(R_Type_Server)

find_package(Threads)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(UnitTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE_FILES
        main.cpp
        GameInstance/GameInstanceManager.cpp Include/GameInstance/GameInstanceManager.hpp GameInstance/GameInstance.cpp Include/GameInstance/GameInstance.hpp GameManager/GameManager.cpp Include/GameManager/GameManager.hpp NetworkManager/NetworkManager.cpp Include/NetworkManager/NetworkManager.hpp ServerEntityPool/ServerEntityPool.cpp Include/ServerEntityPool/ServerEntityPool.hpp)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter -Wno-unused-private-field")
ENDIF()

add_executable(R_Type_Server ${SERVER_SOURCE_FILES})
target_link_libraries(R_Type_Server RTypeShared ${CMAKE_THREAD_LIBS_INIT})
target_compile_definitions(R_Type_Server PRIVATE -DRTYPE_SERVER)
add_custom_command(TARGET R_Type_Server PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/medias $<TARGET_FILE_DIR:R_Type_Server>/medias)