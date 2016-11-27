//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPENETWORKCLIENT_HPP
#define R_TYPE_RTYPENETWORKCLIENT_HPP


#include <thread>

class RTypeNetworkClient {
private:
    std::unique_ptr<std::thread> _networkThread;

public:
    RTypeNetworkClient();

    void RunReceive();

    void Run();

    void Ending();
};


#endif //R_TYPE_RTYPENETWORKCLIENT_HPP
