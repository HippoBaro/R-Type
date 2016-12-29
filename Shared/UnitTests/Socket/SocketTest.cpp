//
// Created by pasteu_e on 29/11/16.
//

#include <gtest/gtest.h>
#include "Socket/IRTypeSocket.hpp"
#include "RTypeSocket.hpp"
#include <thread>

std::string UDPString = "";
std::string TCPString = "";

void UdpCreateServer() {
    char buffer[1024];

    RTypeNetworkPayload payload(buffer, 1024);
    std::unique_ptr<IRTypeSocket> server = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(5678));
    server->Bind();
    while (!server->Receive(payload));
    UDPString = std::string(payload.Payload);
}

void UdpCreateClient() {
    RTypeNetworkPayload payload((char *) "Bonjour server UDP !", (int) strlen("Bonjour server UDP !"));

    std::unique_ptr<IRTypeSocket> client = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>("127.0.0.1", 5678));
    //Waiting 0.5 sec to give the time to UdpCreateServer to pass in the Receive loop.
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
    while (!client->Send(payload));
}

void TcpCreateServer() {
    char buffer[1024];

    RTypeNetworkPayload payload(buffer, 1024);
    std::shared_ptr<IRTypeSocket> server = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>(8769));
    server->Bind();
    std::shared_ptr<IRTypeSocket> client;
    client = server->Accept();
	if (client->PoolEventOnSocket(DATA_INCOMING, -1))
		client->Receive(payload);
    if (client->PoolEventOnSocket(SOMEONE_LISTENING, -1))
        client->Send(payload);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
}

void TcpCreateClient() {
    char buffer[1024];

    RTypeNetworkPayload sendpayload((char *) "Bonjour server TCP !", (int) strlen("Bonjour server TCP !"));
    RTypeNetworkPayload receivepayload(buffer, 1024);
    std::unique_ptr<IRTypeSocket> client = std::unique_ptr<IRTypeSocket>(new RTypeSocket<TCP>("127.0.0.1", 8769));
    while (!client->Connect());
    if (client->PoolEventOnSocket(SOMEONE_LISTENING, -1))
        client->Send(sendpayload);
    if (client->PoolEventOnSocket(DATA_INCOMING, -1))
        client->Receive(receivepayload);
    TCPString = std::string(receivepayload.Payload);
}

TEST(Tests_Socket, UDP_Socket) {
    std::thread t1(UdpCreateServer);
    std::thread t2(UdpCreateClient);
    t1.join();
    t2.join();
    ASSERT_EQ(UDPString, "Bonjour server UDP !");
}

TEST(Tests_Socket, TCP_Socket) {
    std::thread t1(TcpCreateServer);
    std::thread t2(TcpCreateClient);
    t1.join();
    t2.join();
    ASSERT_EQ(TCPString, "Bonjour server TCP !");
}