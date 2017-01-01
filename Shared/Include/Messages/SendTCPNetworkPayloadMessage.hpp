//
// Created by pasteu_e on 20/12/16.
//

#ifndef R_TYPE_SENDTCPNETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_SENDTCPNETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <Socket/IRTypeSocket.hpp>
#include <Socket/RTypeNetworkPayload.h>
#include <Serializer/Packer.hpp>

class SendTCPNetworkPayloadMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::SEND_NET_TCP_MESSAGE;

private:
    const RType::Packer _packer;
    const std::shared_ptr<IRTypeSocket> _destination;

public:
    SendTCPNetworkPayloadMessage(const RType::Packer &packer, std::shared_ptr<IRTypeSocket> const &destination) : _packer(packer), _destination(destination) {}

    const RType::Packer &getPacker() const {
        return _packer;
    }

    const std::shared_ptr<IRTypeSocket> &getDestination() const {
        return _destination;
    }

    const std::shared_ptr<RTypeNetworkPayload> ConvertToSocketMessage() const {
        return std::make_shared<RTypeNetworkPayload>(_packer.getBuffer(), _packer.getLength());
    }
};

#endif //R_TYPE_SENDTCPNETWORKPAYLOADMESSAGE_HPP
