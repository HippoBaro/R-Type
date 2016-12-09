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
        Include/PartitionSegmentBuilder.hpp

        Serializer/Include/IPacker.hpp
        Serializer/WritePacker.cpp
        Serializer/Include/WritePacker.hpp
        Serializer/Include/ISerializable.hpp
        Serializer/Include/SerializationHelper.hpp
        Serializer/Helpers/SerializationHelper.cpp
        Serializer/ReadPacker.cpp
        Serializer/Include/ReadPacker.hpp
        Serializer/SerializationHelper.cpp)

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