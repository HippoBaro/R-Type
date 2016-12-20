//
// Created by pasteu_e on 20/12/16.
//

#ifndef R_TYPE_RECEIVEDTCPNETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_RECEIVEDTCPNETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <Socket/RTypeNetworkPayload.h>

class ReceivedTCPNetworkPayloadMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::RECEIVED_NET_TCP_MESSAGE;

private:
    const RTypeNetworkPayload _payload;

public:
    ReceivedTCPNetworkPayloadMessage(const RTypeNetworkPayload &payload) : _payload(payload) {}

    const RTypeNetworkPayload &getPayload() const {
        return _payload;
    }
};

#endif //R_TYPE_RECEIVEDTCPNETWORKPAYLOADMESSAGE_HPP
