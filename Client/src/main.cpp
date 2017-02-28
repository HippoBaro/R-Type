//
// Created by pasteu_e on 11/21/16.
//

#include <RTypeClient.hpp>

int main(int ac, char **av) {
    std::string serverEndpoint;
    if (ac > 1)
        serverEndpoint = std::string(av[1]);
    RTypeClient client(serverEndpoint);
    client.Run();
    return 0;
}