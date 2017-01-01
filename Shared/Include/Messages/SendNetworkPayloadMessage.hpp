//
// Created by hippolyteb on 12/15/16.
//

#ifndef R_TYPE_SENDNETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_SENDNETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <Socket/RTypeNetworkPayload.h>
#include <Serializer/Packer.hpp>

class SendNetworkPayloadMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::SEND_NET_MESSAGE;

private:
    const RType::Packer _packer;
    const std::string _destination;

public:
    SendNetworkPayloadMessage(const RType::Packer &packer, std::string const &destination) : _packer(packer), _destination(destination) {}
    SendNetworkPayloadMessage(const RType::Packer &packer) : _packer(packer), _destination() {}

    const RType::Packer &getPacker() const {
        return _packer;
    }

    const std::string &getDestination() const {
        return _destination;
    }

    const std::shared_ptr<RTypeNetworkPayload> ConvertToSocketMessage() const {
        return std::make_shared<RTypeNetworkPayload>(RTypeNetworkPayload(_packer.getBuffer(), _packer.getLength(), _destination));
    }
};

#endif //R_TYPE_SENDNETWORKPAYLOADMESSAGE_HPP
