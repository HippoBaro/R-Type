cmake_minimum_required(VERSION 2.6.2)

project(R_Type_Client)

add_subdirectory(UnitTests)

IF (MSVC)
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Shared/Include/Socket/Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_SOCKET_HEADER_FOLDER ../Shared/Include/Socket/UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter -Wno-unused-private-field")
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
        src/SoundManager.cpp

        src/GameContext/ClientEntityPool.cpp

        Includes/RTypeClient.hpp
        Includes/SFMLManager.hpp
        Includes/RTypeInputListener.hpp
        Includes/RTypeGameContext.hpp
        Includes/RTypeMenuContext.hpp
        Includes/RTypeNetworkClient.hpp
        Includes/ClientEntityPool.hpp
        Includes/SoundManager.hpp

        Interfaces/IRTypeDrawingContext.hpp

        Includes/DrawableMenu/ADrawableMenu.hpp
        Includes/DrawableMenu/ADrawableInputMenu.hpp
        Includes/DrawableMenu/MenuRoot.hpp
        Includes/DrawableMenu/MenuSettings.hpp
        Includes/DrawableMenu/MenuCreateRoom.hpp
        Includes/DrawableMenu/MenuJoinRoom.hpp
        Includes/DrawableMenu/MenuJoin.hpp
        Includes/DrawableMenu/MenuCreate.hpp
        Includes/DrawableMenu/MenuMusicVolume.hpp
        Includes/DrawableMenu/MenuSoundVolume.hpp

        src/DrawableMenu/ADrawableMenu.cpp
        src/DrawableMenu/ADrawableInputMenu.cpp
        src/DrawableMenu/MenuRoot.cpp
        src/DrawableMenu/MenuSettings.cpp
        src/DrawableMenu/MenuCreateRoom.cpp
        src/DrawableMenu/MenuJoinRoom.cpp
        src/DrawableMenu/MenuJoin.cpp
        src/DrawableMenu/MenuCreate.cpp
        src/DrawableMenu/MenuMusicVolume.cpp
        src/DrawableMenu/MenuSoundVolume.cpp
        src/DrawableMenu/MenuSelectLevel.cpp Includes/DrawableMenu/MenuSelectLevel.hpp)

add_executable(R_Type_Client ${CLIENT_SOURCE_FILES})
target_compile_definitions(R_Type_Client INTERFACE -DRTYPE_CLIENT)
target_link_libraries(R_Type_Client RTypeShared sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_command(TARGET R_Type_Client PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/medias $<TARGET_FILE_DIR:R_Type_Client>/medias)