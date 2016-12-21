//
// Created by hippolyteb on 12/18/16.
//

#ifndef R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>

class ReceiveNetworkPayloadMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::RECEIVE_NET_MESSAGE;

private:
    uint16_t _maxPayload;

public:
    ReceiveNetworkPayloadMessage(uint16_t maxPayload) : _maxPayload(maxPayload) {}

    uint16_t getMaxPayload() const {
        return _maxPayload;
    }
};

#endif //R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP
