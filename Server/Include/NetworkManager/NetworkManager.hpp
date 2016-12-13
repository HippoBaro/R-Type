//
// Created by hippolyteb on 12/12/16.
//

#ifndef R_TYPE_NETWORKMANAGER_HPP
#define R_TYPE_NETWORKMANAGER_HPP


#include <thread>

class NetworkManager {
private:
    std::unique_ptr<std::thread> _thread = nullptr;

private:
    void Run();

public:
    void Start();
};


#endif //R_TYPE_NETWORKMANAGER_HPP
