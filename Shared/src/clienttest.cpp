//
// Created by barre_k on 23/11/16.
//

#include "RTypeSocket.hpp"

int main()
{
    RTypeSocket client =  RTypeSocket();

    client.InitConnection("localhost");
    client.WriteServer("dimitri");
    client.CRun();

    return 0;
}