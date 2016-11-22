cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_LOADER_FILES InternalLinuxLibraryLoader.hpp InternalLinuxLibraryLoader.cpp ExternalClassFactoryLoader.hpp ManagedExternalInstance.hpp ExternalClassFactory.hpp)

add_library(LibraryLoader ${LIBRARY_LOADER_FILES})
target_link_libraries(LibraryLoader ${CMAKE_DL_LIBS})