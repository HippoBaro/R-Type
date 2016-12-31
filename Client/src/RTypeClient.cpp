//
// Created by pasteu_e on 26/11/16.
//

#include "RTypeClient.hpp"

void RTypeClient::Run() {
    _sfmlManager->Run();
}

RTypeClient::RTypeClient(const std::string &serverEndpoint) : _networkClient(std::make_shared<RTypeNetworkClient>(_eventManager, serverEndpoint)) {

}
