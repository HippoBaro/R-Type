//
// Created by barre_k on 23/11/16.
//

#include "RTypeSocket.hpp"

int main()
{
    Payload *client_payload;
    Payload *server_payload;
    RTypeSocket client = RTypeSocket();

    client.InitConnection("localhost", 2323);
    client_payload = client.GetNativePayload();

    client.Send("dimitri");
    while (true)
    {
        if ((server_payload = client.Receive()) != nullptr)
        {
            std::cout << "server messages" << server_payload->_buffer << std::endl;
        }
    }

    return (0);
}