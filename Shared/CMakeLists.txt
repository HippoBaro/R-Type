cmake_minimum_required(VERSION 2.6.2)

add_subdirectory(UnitTests)
add_subdirectory(LibraryLoader)

set(SHARED_SOURCE_FILES
        src/main.cpp
        EntityPool/EntityPool.cpp

        Serializer/ISerializable.cpp
        Serializer/ISerializable.hpp
        Serializer/ISerializerBuffer.hpp
        Serializer/SerializeBuffer.cpp
        Serializer/SerializeBuffer.hpp
        Serializer/DeserializeBuffer.cpp
        Serializer/DeserializeBuffer.hpp

        Include/EntityPool/EntityPool.hpp

        Include/Entities/Trait.hpp
        Include/Entities/Entity.hpp
        Include/Entities/PlayerRef.hpp

        Include/EventDispatcher/EventListener.hpp
        Include/EventDispatcher/EventManager.hpp
        Include/EventDispatcher/Events.h
        Include/EventDispatcher/IMessage.hpp

        Include/PartitionSystem/EntityPartition.hpp
        Include/PartitionSystem/EntityPartitionBuilder.hpp
        Include/PartitionSystem/PartitionSegment.hpp
        Include/PartitionSystem/PartitionSegmentBuilder.hpp
        Include/PartitionSystem/Tween/Tween.hpp
        Include/PartitionSystem/Tween/Curve/EaseInCurve.hpp
        Include/PartitionSystem/Tween/Curve/EaseInOutCurve.hpp
        Include/PartitionSystem/Tween/Curve/EaseOutCurve.hpp
        Include/PartitionSystem/Tween/Curve/ITweeningCurve.hpp
        Include/PartitionSystem/Tween/Curve/LinearCurve.hpp
        Include/PartitionSystem/Tween/Curve/SmoothStepCurve.hpp

        Include/Socket/IRTypeSocket.hpp
        Include/Socket/RTypeNetworkPayload.h
        Include/Socket/Enum/RTypeSocketType.h

        Include/Time/Timer.hpp
        Include/Time/TimeRef.hpp

        Include/IService.hpp
        Include/vec2.hpp

        Include/Messages/FireProjectileMessage.hpp
        Include/Messages/ProjectilePositionChangedMessage.hpp
        Include/Messages/UserInputMessage.hpp
        Include/Messages/MenuLobbyMessage.hpp
        Include/Messages/SoundSystemMessage.hpp
        Include/Json/Json.hpp
        )

include_directories(Libs/Interfaces
        ../SFML/include
        LibraryLoader
        Include/Socket/Enum
        Include/Socket
        ../SharedLibs/Interfaces)

IF (MSVC)
    set(SHARED_SOURCE_FILES ${SHARED_SOURCE_FILES} Include/Socket/Windows/RTypeSocket.hpp)
    set(LIB_SOCKET ws2_32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    set(SHARED_SOURCE_FILES ${SHARED_SOURCE_FILES} Include/Socket/UNIX/RTypeSocket.hpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wuninitialized -Winit-self -Weffc++ -Wno-unused-parameter -Wno-unused-private-field")
ENDIF()

add_library(RTypeShared STATIC ${SHARED_SOURCE_FILES})

target_link_libraries(RTypeShared LibraryLoader ${LIB_SOCKET})