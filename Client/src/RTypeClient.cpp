//
// Created by pasteu_e on 26/11/16.
//

#include "RTypeClient.hpp"

RTypeClient::RTypeClient() : _networkClient(new RTypeNetworkClient()), _sfmlClient(new SFMLManager()) {

}

void RTypeClient::Run() {
    _networkClient->Run();
    _sfmlClient->Run();
    _networkClient->Ending();
}