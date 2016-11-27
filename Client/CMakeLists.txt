cmake_minimum_required(VERSION 2.6.2)

project(R_Type_Client)

add_subdirectory(UnitTests)
add_subdirectory(SFML EXCLUDE_FROM_ALL)
include_directories(SYSTEM "SFML/include/")
include_directories(Includes Interfaces)
include_directories(../Shared/LibraryLoader/ ../Shared/Libs/Interfaces ../Shared/Include)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

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

        Interfaces/IRtypeDrawingContext.hpp
        )

add_executable(R_Type_Client ${CLIENT_SOURCE_FILES})
target_link_libraries(R_Type_Client sfml-graphics sfml-window sfml-system)
