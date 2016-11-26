cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_SOURCE_FILES src/main.cpp Time/TimeRef.cpp Include/TimeRef.hpp Time/Timer.cpp Include/Timer.hpp Include/Tween.hpp Include/ITweeningCurve.hpp Tween/Curve/LinearCurve.cpp Include/LinearCurve.hpp Tween/Curve/SmoothStepCurve.cpp Include/SmoothStepCurve.hpp Tween/Curve/EaseInCurve.cpp Include/EaseInCurve.hpp Tween/Curve/EaseInOutCurve.cpp Include/EaseInOutCurve.hpp Tween/Curve/EaseOutCurve.cpp Include/EaseOutCurve.hpp Include/vec2.hpp PartitionSystem/EntityPartition/EntityPartition.cpp PartitionSystem/EntityPartition/EntityPartition.hpp Libs/Interfaces/IEntity.hpp PartitionSystem/EntityPartition/PartitionSegment.cpp PartitionSystem/EntityPartition/PartitionSegment.hpp PartitionSystem/EntityPartition/PartitionSegmentBuilder.cpp PartitionSystem/EntityPartition/PartitionSegmentBuilder.hpp Include/IService.hpp)

include_directories(Libs/Interfaces)
include_directories(Include)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)