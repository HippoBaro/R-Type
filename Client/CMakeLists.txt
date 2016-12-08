cmake_minimum_required(VERSION 2.6.2)

project(R_Type_Client)

add_subdirectory(UnitTests)

IF (MSVC)
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Shared/Include/Socket/Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Shared/Include/Socket/UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter -Wno-unused-private-field")
ENDIF()

include_directories(Includes Interfaces ${LIBRARY_SOCKET_HEADER_FOLDER})


include_directories(SYSTEM "../SFML/include/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_SOURCE_FILES
        src/main.cpp
        src/RTypeClient.cpp
        src/SFMLManager.cpp
        src/RTypeInputListener.cpp
        src/RTypeGameContext.cpp
        src/RTypeMenuContext.cpp
        src/RTypeNetworkClient.cpp

        Includes/RTypeClient.hpp
        Includes/SFMLManager.hpp
        Includes/RTypeInputListener.hpp
        Includes/RTypeGameContext.hpp
        Includes/RTypeMenuContext.hpp
        Includes/RTypeNetworkClient.hpp

        Interfaces/IRTypeDrawingContext.hpp
        src/GameContext/ClientEntityPool.cpp Includes/ClientEntityPool.hpp ../SharedLibs/Interfaces/TextureBag.hpp
        src/SoundManager.cpp
        Includes/SoundManager.hpp
        Includes/DrawableMenu/ADrawableMenu.hpp
        Includes/DrawableMenu/MenuRoot.hpp
        Includes/DrawableMenu/MenuSettings.hpp
        Includes/DrawableMenu/MenuCreate.hpp
        Includes/DrawableMenu/MenuJoin.hpp
        )

add_executable(R_Type_Client ${CLIENT_SOURCE_FILES})
target_link_libraries(R_Type_Client RTypeShared sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_command(TARGET R_Type_Client PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Client/sprites $<TARGET_FILE_DIR:R_Type_Client>/sprites)