cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_SOURCE_FILES src/main.cpp Time/TimeRef.cpp Include/TimeRef.hpp Time/Timer.cpp Include/Timer.hpp Include/Tween.hpp Include/ITweeningCurve.hpp Tween/Curve/LinearCurve.cpp Include/LinearCurve.hpp Tween/Curve/SmoothStepCurve.cpp Include/SmoothStepCurve.hpp Tween/Curve/EaseInCurve.cpp Include/EaseInCurve.hpp Tween/Curve/EaseInOutCurve.cpp Include/EaseInOutCurve.hpp Tween/Curve/EaseOutCurve.cpp Include/EaseOutCurve.hpp Include/vec2.hpp PartitionSystem/EntityPartition/EntityPartition.cpp Libs/Interfaces/Entity.hpp PartitionSystem/EntityPartition/PartitionSegment.cpp PartitionSystem/EntityPartition/PartitionSegmentBuilder.cpp PartitionSystem/EntityPartition/EntityPartitionBuilder.cpp Include/IService.hpp
        EventDispatcher/EventManager.cpp
        Include/EventListener.hpp
        Include/EventManager.hpp
        Include/Events.h Libs/Interfaces/IDrawable.hpp EntityPool/EntityPool.cpp Include/EntityPool.hpp Libs/Trait.hpp Libs/Interfaces/DrawableEntity.hpp)

include_directories(Include Libs/Interfaces ../Client/SFML/include LibraryLoader)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared SHARED ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)