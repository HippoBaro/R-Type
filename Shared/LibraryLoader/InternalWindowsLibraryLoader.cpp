//
// Created by hippolyteb on 11/22/16.
//

#include "LibraryLoader/InternalWindowsLibraryLoader.hpp"
#include <windows.h>

std::shared_ptr<ExternalClassFactory> InternalLibraryLoader::GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor, std::string const &destructor) {
    
	auto dllpath = libraryPath + libName;
	dllpath = dllpath + std::string(".dll");
	HMODULE myDll = LoadLibrary(dllpath.c_str());

    if(myDll == nullptr)
        throw std::runtime_error("Unable to load library");

    create_t *create = (create_t *)(GetProcAddress(myDll, constructor.c_str()));
    if(create == nullptr)
        throw std::runtime_error("Unable to load library");

    destroy_t *destroy = (destroy_t *) GetProcAddress(myDll, destructor.c_str());
    if(destroy == nullptr)
        throw std::runtime_error("Unable to load library");
    return std::make_shared<ExternalClassFactory>(create, destroy, myDll, libName, [&](void *ptr) { this->DestroyFactory(ptr); });
}

void InternalLibraryLoader::DestroyFactory(void *factory) {
    FreeLibrary((HMODULE)factory);
}
