//
// Created by barre_k on 23/11/16.
//

#include "RTypeSocket.hpp"

int main() {
    RTypeSocket client = RTypeSocket();
    bool gamecondition = true;
    char lol[] = "wala ca marche";
    char *messageofserver;


    client.InitConnection("localhost");
    client.WriteServer("joueur numero 1");
    client.WriteServer("nique");
    client.WriteServer(lol);
    while (gamecondition)
    {
        messageofserver = client.ListenServer();
        if (messageofserver != nullptr)
        {
            std::cout << "message of server " << messageofserver << " " << std::string(messageofserver) << std::endl;
        }
    }
    client.EndConnection();
    return 0;
}