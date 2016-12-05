//
// Created by hippolyteb on 11/20/16.
//

#include <gtest/gtest.h>
#include "../../src/RTypeSocket.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>


std::chrono::system_clock::rep time_since_epoch() {
    static_assert(
            std::is_integral<std::chrono::system_clock::rep>::value,
            "Representation of ticks isn't an integral value."
    );
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

void Testserver() {
    Payload *client;
    Payload *server_payload;

    RTypeSocket server = RTypeSocket();
    server.InitConnection(2323);
    server_payload = server.GetNativePayload();
    bool condition = true;

    while (condition)
    {
        if ((client = server.Receive()) != nullptr) {
            std::cout << "socket server = " << client->_sock << " addresse " << client->_sin.sin_addr.s_addr << std::endl;
            std::cout << "client buffer = " << client->_buffer << std::endl;
            if (strcmp(client->_buffer, "stop") == 0)
                condition = false;
            std::cout << "condition " << condition << std::endl;
            server.Send(client, "message recu");
        }
    }
}

void Testclient()
{
    Payload *client_payload;
    Payload *server_payload;
    RTypeSocket client = RTypeSocket();
    client.InitConnection("localhost", 2323);
    client_payload = client.GetNativePayload();
    char cpt = 0;

    client.Send("dimitri");
    client.Send("dimitri");
    client.Send("dimitri");
    client.Send("dimitri");
    client.Send("dimitri");
    client.Send("dimitri");
    client.Send("stop");
    client.Send("lol");
    client.Send("lol");
    while (cpt++ < 7)
    {
        if ((server_payload = client.Receive()) != nullptr)
        {
            std::cout << "server messages" << server_payload->_buffer << std::endl;
        }
    }
}

TEST(Tests_Socket_UDP, CanBindToValidEndpoint) {
    std::thread server (Testserver);
    std::thread client (Testclient);

    client.join();
    server.join();
}

TEST(Tests_Socket_UDP, CanBindToInvalidEndpoint) {
    ASSERT_EQ(1 * 2, 2) << "This will fail !";
}