//
// Created by hippolyteb on 11/22/16.
//

#include "InternalWindowsLibraryLoader.hpp"
#include <windows.h>

ExternalClassFactory InternalLibraryLoader::GetFactoryForClass(std::string libraryPath, std::string const &constructor, std::string const &destructor) {
    HMODULE myDll = LoadLibrary(libraryPath.c_str());

    if(myDll == nullptr)
        throw std::runtime_error("Unable to load library");

    create_t *create = (create_t *)(GetProcAddress(myDll, constructor.c_str()));
    if(create == nullptr)
        throw std::runtime_error("Unable to load library");

    destroy_t *destroy = (destroy_t *) GetProcAddress(myDll, destructor.c_str());
    if(destroy == nullptr)
        throw std::runtime_error("Unable to load library");
    return ExternalClassFactory(create, destroy, myDll, libraryPath, [&](void *ptr) { this->DestroyFactory(ptr); });
}

void InternalLibraryLoader::DestroyFactory(void *factory) {
    FreeLibrary(factory);
}
