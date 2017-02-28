//
// Created by Hippolyte Barraud on 31/12/2016.
//

#ifndef R_TYPE_APPLICATIONQUITMESSAGE_HPP
#define R_TYPE_APPLICATIONQUITMESSAGE_HPP

#include <Serializer/ISerializable.hpp>
#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>

class ApplicationQuitMessage : public IMessage, RType::ISerializable {
public:
    static constexpr RType::Event EventType = RType::APP_QUIT;

public:
    ApplicationQuitMessage() {};

};

#endif //R_TYPE_APPLICATIONQUITMESSAGE_HPP
