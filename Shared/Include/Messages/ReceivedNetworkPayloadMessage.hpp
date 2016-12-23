//
// Created by hippolyteb on 12/19/16.
//

#ifndef R_TYPE_RECEIVEDNETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_RECEIVEDNETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <Socket/RTypeNetworkPayload.h>

class ReceivedNetworkPayloadMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::RECEIVED_NET_MESSAGE;

private:
    const std::shared_ptr<RTypeNetworkPayload> _payload;

public:
    ReceivedNetworkPayloadMessage(const std::shared_ptr<RTypeNetworkPayload> &payload) : _payload(payload) {}

    const std::shared_ptr<RTypeNetworkPayload> &getPayload() const {
        return _payload;
    }
};

#endif //R_TYPE_RECEIVEDNETWORKPAYLOADMESSAGE_HPP
