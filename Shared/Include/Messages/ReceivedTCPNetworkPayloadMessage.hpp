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
    const uint8_t _id;
    const std::shared_ptr<RTypeNetworkPayload> _payload;

public:
    ReceivedTCPNetworkPayloadMessage(const uint8_t id, const std::shared_ptr<RTypeNetworkPayload> &payload) : _id(id), _payload(payload) {}

    uint8_t getId() const {
        return _id;
    }

    const std::shared_ptr<RTypeNetworkPayload> &getPayload() const {
        return _payload;
    }
};

#endif //R_TYPE_RECEIVEDTCPNETWORKPAYLOADMESSAGE_HPP
