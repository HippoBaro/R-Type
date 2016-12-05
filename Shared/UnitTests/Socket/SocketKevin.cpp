//
// Created by barre_k on 05/12/16.
//


#include <gtest/gtest.h>
#include "RTypeSocket.hpp"
#include <thread>

std::string message;

void create_server()
{
    RTypeSocket server = RTypeSocket();
    Payload *client;
    server.InitConnection(4242);
    if ((client = server.Receive()) != nullptr) {
        message = client->_buffer;
    }
}

void create_client() {
    RTypeSocket client = RTypeSocket();
    client.InitConnection("localhost", 4242);
    client.Send("message");
}

TEST(Tests_Socket_UDP, Creation) {
    std::thread t1(create_server);
    std::thread t2(create_client);
    t1.join();
    t2.join();
    ASSERT_EQ(message, "message");
}