//
// Created by hippolyteb on 11/20/16.
//

#include <iostream>
#include <ManagedExternalInstance.hpp>
#include <ITest.hpp>
#include <ExternalClassFactoryLoader.hpp>

int main() {

    try {
        ManagedExternalInstance<ITest> poly = ExternalClassFactoryLoader::GetInstanceOf<ITest>("../SharedLibs/Test/libTest.so");
		poly->Test();
    }
    catch (std::exception e) {

    }

	std::cin.get();
}