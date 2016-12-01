cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(LIBRARY_SOCKET_FILES
        Socket/Interfaces/IRTypeSocket.hpp
        Socket/Includes/RTypeNetworkPayload.h
        Socket/Enum/RTypeSocketType.h)


set(SHARED_SOURCE_FILES
        src/main.cpp
        Include/TimeRef.hpp
        Include/Timer.hpp
        Include/PartitionSystem/Tween/Tween.hpp
        Include/PartitionSystem/Tween/Curve/ITweeningCurve.hpp
        Include/PartitionSystem/Tween/Curve/LinearCurve.hpp
        Include/PartitionSystem/Tween/Curve/SmoothStepCurve.hpp
        Include/PartitionSystem/Tween/Curve/EaseInCurve.hpp
        Include/PartitionSystem/Tween/Curve/EaseInOutCurve.hpp
        Include/PartitionSystem/Tween/Curve/EaseOutCurve.hpp
        Include/vec2.hpp
        Libs/Interfaces/Entity.hpp
        Include/IService.hpp
        EventDispatcher/EventManager.cpp
        Include/EventDispatcher/EventListener.hpp
        Include/EventDispatcher/EventManager.hpp
        Include/EventDispatcher/Events.h
        Libs/Interfaces/IDrawable.hpp
        EntityPool/EntityPool.cpp
        Include/EntityPool/EntityPool.hpp
        Libs/Trait.hpp
        Libs/Interfaces/DrawableEntity.hpp
        Include/PartitionSystem/EntityPartition.hpp
        Include/PartitionSystem/EntityPartitionBuilder.hpp
        Include/EntityPool/EntityPool.hpp
        Include/PartitionSystem/PartitionSegment.hpp
        Include/PartitionSystem/PartitionSegmentBuilder.hpp)

include_directories(Include Libs/Interfaces ../SFML/include LibraryLoader Socket/ Socket/Interfaces Socket/Enum)

IF (MSVC)
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Socket/Windows/RTypeSocket.hpp)
    set(LIB_SOCKET ws2_32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(LIBRARY_SOCKET_FILES ${LIBRARY_SOCKET_FILES} Socket/Linux/RTypeSocket.hpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unused-parameter")
ENDIF()

add_library(RTypeShared STATIC ${SHARED_SOURCE_FILES} ${LIBRARY_SOCKET_FILES})
target_link_libraries(RTypeShared LibraryLoader ${LIB_SOCKET})