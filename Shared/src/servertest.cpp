//
// Created by barre_k on 22/11/16.
//

#include "RTypeSocket.hpp"

int main()
{
    Payload *server_payload;
    Payload *client;
    RTypeSocket server = RTypeSocket();

    server.InitConnection(2323);
    server_payload = server.GetNativePayload();
    std::cout << "socket server_payload = " << server_payload->_sock << std::endl;

    while (true)
    {
        if ((client = server.Receive()) != nullptr)
        {
            std::cout << "socket server = " << client->_sock << " addresse "
             << client->_sin.sin_addr.s_addr  << std::endl;
            std::cout << "client buffer = " << client->_buffer << std::endl;
            server.Send(client, "message recu");
        }
    }

}