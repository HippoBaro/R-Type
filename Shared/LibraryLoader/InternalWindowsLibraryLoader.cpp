//
// Created by hippolyteb on 11/22/16.
//

#include "InternalWindowsLibraryLoader.hpp"
#include <windows.h>

ExternalClassFactory InternalLibraryLoader::GetFactoryForClass(std::string libraryPath) {
    HMODULE myDll = LoadLibrary("C:\\R-Type\\build\\SharedLibs\\Test\\Debug\\Test.dll");

    if(myDll == nullptr)
        return ExternalClassFactory();

    create_t *create = (create_t *)(GetProcAddress(myDll, "create"));
    if(create == nullptr)
        return ExternalClassFactory();

    destroy_t *destroy = (destroy_t *) GetProcAddress(myDll,"destroy");
    if(destroy == nullptr)
        return ExternalClassFactory();
    return ExternalClassFactory(create, destroy);
}
