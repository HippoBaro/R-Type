//
// Created by hippolyteb on 11/20/16.
//

#include <iostream>
#include "../../Shared/Libs/Interfaces/ITest.hpp"
#include "../../Shared/LibraryLoader/ExternalClassFactoryLoader.hpp"

int main() {

    try {
        ManagedExternalInstance<ITest> poly = ExternalClassFactoryLoader::GetInstanceOf<ITest>("/home/hippolyteb/.CLion2016.2/system/cmake/generated/R-Type-32b3c3e3/32b3c3e3/Debug2/SharedLibs/Test/libTest.so");
        poly->Test();
    }
    catch (std::exception e) {

    }
}