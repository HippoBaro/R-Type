cmake_minimum_required(VERSION 2.6.2)


add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)
#add_subdirectory(Socket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SHARED_SOURCE_FILES
        src/RTypeSocket.hpp
        src/IRTypeSocket.hpp
        src/RTypeSocket.hpp
        src/RTypeSocket.cpp
        Include/TimeRef.hpp
        Include/Timer.hpp
        Include/Tween.hpp
        Include/ITweeningCurve.hpp
        Include/LinearCurve.hpp
        Include/SmoothStepCurve.hpp
        Include/EaseInCurve.hpp
        Include/EaseInOutCurve.hpp
        Include/EaseOutCurve.hpp
        Include/vec2.hpp
        Libs/Interfaces/Entity.hpp
        Include/IService.hpp
        EventDispatcher/EventManager.cpp
        Include/EventListener.hpp
        Include/EventManager.hpp
        Include/Events.h
        Libs/Interfaces/IDrawable.hpp
        EntityPool/EntityPool.cpp
        Include/EntityPool.hpp
        Libs/Trait.hpp
        Libs/Interfaces/DrawableEntity.hpp
        Include/EntityPartition.hpp
        Include/EntityPartitionBuilder.hpp
        Include/EntityPool.hpp
        Include/PartitionSegment.hpp
        Include/PartitionSegmentBuilder.hpp)

include_directories(Include Libs/Interfaces ../SFML/include LibraryLoader Socket)

IF (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared STATIC ${SHARED_SOURCE_FILES})
target_link_libraries(RTypeShared LibraryLoader)
