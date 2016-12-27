//
// Created by hippolyteb on 11/22/16.
//

#include "LibraryLoader/InternalLinuxLibraryLoader.hpp"

std::shared_ptr<ExternalClassFactory> InternalLibraryLoader::GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor, std::string const &destructor) {
    // load the triangle library

#if(APPLE)
    std::string ext = ".dylib";
#else
    std::string ext = ".so";
#endif
    std::string lib = (libraryPath + "lib" + libName + ext);

    void *factory = dlopen(lib.c_str(), RTLD_LAZY);
    if (!factory)
        throw std::runtime_error("Unable to load library");

    create_t *create_triangle = (create_t*) dlsym(factory, constructor.c_str());
    const char *dlsym_error = dlerror();
    if (dlsym_error)
        throw std::runtime_error("Unable to load library");

    destroy_t* destroy_triangle = (destroy_t*) dlsym(factory, destructor.c_str());
    dlsym_error = dlerror();
    if (dlsym_error)
        throw std::runtime_error("Unable to load library");
    return std::make_shared<ExternalClassFactory>(create_triangle, destroy_triangle, factory, libName, [&](void *ptr) { this->DestroyFactory(ptr); });
}

void InternalLibraryLoader::DestroyFactory(void *factory) {
    dlclose(factory);
}
