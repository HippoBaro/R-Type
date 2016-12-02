cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_LOADER_FILES
        ../Include/LibraryLoader/ExternalClassFactoryLoader.hpp
        ../Include/LibraryLoader/ManagedExternalInstance.hpp
        ../Include/LibraryLoader/ExternalClassFactory.hpp)

IF (MSVC)
    set(LIBRARY_LOADER_FILES ${LIBRARY_LOADER_FILES}
            ../Include/LibraryLoader/InternalWindowsLibraryLoader.hpp
            InternalWindowsLibraryLoader.cpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_LOADER_FILES ${LIBRARY_LOADER_FILES}
            ../Include/LibraryLoader/InternalLinuxLibraryLoader.hpp
            InternalLinuxLibraryLoader.cpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(LibraryLoader STATIC ${LIBRARY_LOADER_FILES})
target_link_libraries(LibraryLoader ${CMAKE_DL_LIBS})