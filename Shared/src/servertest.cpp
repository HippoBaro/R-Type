//
// Created by barre_k on 22/11/16.
//

#include "RTypeSocket.hpp"

int main()
{
    RTypeSocket server =  RTypeSocket();

    server.InitConnection();
    server.SRun();
    return 0;
}