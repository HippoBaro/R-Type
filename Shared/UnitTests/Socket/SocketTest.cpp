//
// Created by pasteu_e on 29/11/16.
//

#include <gtest/gtest.h>
#include "RTypeSocket.hpp"
#include <thread>

RTypeNetworkPayload globalPayload;

void create_server() {
    RTypeSocket server = RTypeSocket();
    server.Bind();
    for (int i = 0; i < 100000; ++i) {
        server.Receive(globalPayload, 1024);
        if (!globalPayload._isEmpty) {
            break;
        }
    }
}

void create_client() {
    RTypeSocket client = RTypeSocket("127.0.0.1");
    for (int i = 0; i < 100000; ++i) {
        client.Send("Bonjour server !");
    }
}

TEST(Tests_Socket_UDP, Creation) {
    std::thread t1(create_server);
    std::thread t2(create_client);
    t1.join();
    t2.join();
    ASSERT_EQ(globalPayload._isEmpty, false);
    ASSERT_EQ(globalPayload._payload, "Bonjour server !");
}