//
// Created by Etienne Pasteur on 25/12/2016.
//

#ifndef R_TYPE_CLIENTWAITFORSERVERMESSAGE_H
#define R_TYPE_CLIENTWAITFORSERVERMESSAGE_H

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>

enum ClientType {
    USER_CREATE,
    USER_JOIN,
    USER_QUIT
};

class ClientWaitForServerMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::MENU_LOBBY;

private:
    const ClientType _event;
    std::string _channelName;

public:
    ClientWaitForServerMessage(const ClientType &event, const std::string &channelName) : _event(event), _channelName(channelName) {}

    const std::string &getChannelName() const {
        return _channelName;
    }

    const ClientType &getEventType() const {
        return _event;
    }
};

#endif //R_TYPE_CLIENTWAITFORSERVERMESSAGE_H
