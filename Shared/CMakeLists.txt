cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_SOURCE_FILES src/main.cpp Time/TimeRef.cpp Include/TimeRef.hpp Time/Timer.cpp Include/Timer.hpp Include/Tween.hpp Include/ITweeningCurve.hpp Tween/Curve/LinearCurve.cpp Include/LinearCurve.hpp Tween/Curve/SmoothStepCurve.cpp Include/SmoothStepCurve.hpp Tween/Curve/EaseInCurve.cpp Include/EaseInCurve.hpp Tween/Curve/EaseInOutCurve.cpp Include/EaseInOutCurve.hpp Tween/Curve/EaseOutCurve.cpp Include/EaseOutCurve.hpp
        EventDispatcher/EventManager.cpp
        Include/EventListener.hpp
        Include/EventManager.hpp
        Include/Events.h)

include_directories(Libs/Interfaces)
include_directories(Include)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)