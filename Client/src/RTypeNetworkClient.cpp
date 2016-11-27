//
// Created by pasteu_e on 27/11/16.
//

#include <memory>
#include <iostream>
#include "RTypeNetworkClient.hpp"

RTypeNetworkClient::RTypeNetworkClient() : _networkThread(nullptr) {

}

void RTypeNetworkClient::RunReceive() {
    while (true) {
        std::cout << "Waiting for incoming message from server" << std::endl;
        //TODO : Send incoming message to eventEmitter here !
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
    }
}

void RTypeNetworkClient::Run() {
    _networkThread = std::unique_ptr<std::thread>(new std::thread(std::bind(&RTypeNetworkClient::RunReceive, this)));
}

void RTypeNetworkClient::Ending() {
    //Here to avoid "terminate called without an active exception" error
    _networkThread->detach();
}

