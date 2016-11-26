//
// Created by barre_k on 22/11/16.
//

#include "RTypeSocket.hpp"

int main()
{
    char str[] = "azertyuiopqsdfghjklmwxcvbn AZERTYUIOPQSDFGHJKLMWXCVBN";
    char *ptr;
    ptr = str;
    RTypeSocket server =  RTypeSocket();
    char *messageofclient;
    bool gamecondition = true;

    server.InitConnection();
    while (gamecondition)
    {
        messageofclient = server.ListenClient();
        if (messageofclient != nullptr)
        {
            std::cout << "messageofclient " << messageofclient << std::endl;

            server.SendMessageToAllClients("message recu");
        }
    }
    server.EndConnection();
    return 0;
}