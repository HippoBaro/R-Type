//
// Created by pasteu_e on 29/11/16.
//

#include <gtest/gtest.h>
#include "Socket/IRTypeSocket.hpp"
#include "RTypeSocket.hpp"
#include <thread>

RTypeNetworkPayload globalPayload;

void UdpCreateServer() {
    std::unique_ptr<IRTypeSocket> server = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(5678));
    server->Bind();
    for (int i = 0; i < 100000; ++i) {
        if (server->Receive(globalPayload, 1024)) {
            break;
        }
    }
}

void UdpCreateClient() {
    std::unique_ptr<IRTypeSocket> client = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>("127.0.0.1", 5678));
    for (int i = 0; i < 100000; ++i) {
        client->Send("Bonjour server UDP !");
    }
}

void TcpCreateServer() {
    std::unique_ptr<IRTypeSocket> server = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(8769));
    server->Bind();
    std::unique_ptr<IRTypeSocket> newClient = server->Accept();
    newClient->Receive(globalPayload, 1024);
}

void TcpCreateClient() {
    std::unique_ptr<IRTypeSocket> client = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>("127.0.0.1", 8769));
    while (!client->Connect());
    client->Send("Bonjour server TCP !");
}

TEST(Tests_Socket, UDP_Socket) {
    std::thread t1(UdpCreateServer);
    std::thread t2(UdpCreateClient);
    t1.join();
    t2.join();
    ASSERT_EQ(globalPayload.Payload, "Bonjour server UDP !");
}

TEST(Tests_Socket, TCP_Socket) {
    std::thread t1(TcpCreateServer);
    std::thread t2(TcpCreateClient);
    t1.join();
    t2.join();
    ASSERT_EQ(globalPayload.Payload, "Bonjour server TCP !");
}