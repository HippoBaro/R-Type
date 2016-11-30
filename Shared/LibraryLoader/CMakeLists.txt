cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_LOADER_FILES
        ExternalClassFactoryLoader.hpp
        ManagedExternalInstance.hpp
        ExternalClassFactory.hpp)
include_directories(../Include)

IF (MSVC)
    set(LIBRARY_LOADER_FILES ${LIBRARY_LOADER_FILES}
            InternalWindowsLibraryLoader.hpp
            InternalWindowsLibraryLoader.cpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_LOADER_FILES ${LIBRARY_LOADER_FILES}
            InternalLinuxLibraryLoader.hpp
            InternalLinuxLibraryLoader.cpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(LibraryLoader STATIC ${LIBRARY_LOADER_FILES})
target_link_libraries(LibraryLoader ${CMAKE_DL_LIBS})