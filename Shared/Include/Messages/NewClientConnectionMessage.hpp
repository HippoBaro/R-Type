//
// Created by pasteu_e on 20/12/16.
//

#ifndef R_TYPE_NEWCLIENTCONNECTIONMESSAGE_HPP
#define R_TYPE_NEWCLIENTCONNECTIONMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <Socket/RTypeNetworkPayload.h>
#include <Socket/IRTypeSocket.hpp>

class NewClientConnectionMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::NEW_CLIENT_CONNECTION;

private:
    std::shared_ptr<IRTypeSocket> _client;

public:
    NewClientConnectionMessage(std::shared_ptr<IRTypeSocket> &client) : _client(client) {}

    std::shared_ptr<IRTypeSocket> getClient() {
        return _client;
    }
};

#endif //R_TYPE_NEWCLIENTCONNECTIONMESSAGE_HPP
