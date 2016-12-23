//
// Created by Hippolyte Barraud on 23/12/2016.
//

#ifndef R_TYPE_STOPRECEIVENETWORKGAMEPAYLOAD_HPP
#define R_TYPE_STOPRECEIVENETWORKGAMEPAYLOAD_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>

class StopReceiveNetworkGamePayload : public IMessage {
public:
    static constexpr RType::Event EventType = RType::STOP_RECEIVE_NET_MESSAGE;

public:
    StopReceiveNetworkGamePayload() {}
};

#endif //R_TYPE_STOPRECEIVENETWORKGAMEPAYLOAD_HPP
