cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SHARED_SOURCE_FILES src/main.cpp Time/TimeRef.cpp Time/TimeRef.hpp Time/Timer.cpp Time/Timer.hpp Tween/Tween.hpp Tween/ITweeningCurve.hpp Tween/Curve/LinearCurve.cpp Tween/Curve/LinearCurve.hpp Tween/Curve/SmoothStepCurve.cpp Tween/Curve/SmoothStepCurve.hpp Tween/Curve/EaseInCurve.cpp Tween/Curve/EaseInCurve.hpp Tween/Curve/EaseInOutCurve.cpp Tween/Curve/EaseInOutCurve.hpp Tween/Curve/EaseOutCurve.cpp Tween/Curve/EaseOutCurve.hpp)

include_directories(Libs/Interfaces)

add_library(RTypeShared ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)