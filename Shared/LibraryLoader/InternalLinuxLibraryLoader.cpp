//
// Created by hippolyteb on 11/22/16.
//

#include "InternalLinuxLibraryLoader.hpp"

ExternalClassFactory InternalLibraryLoader::GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor, std::string const &destructor) {
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
    return ExternalClassFactory(create_triangle, destroy_triangle, factory, libraryPath, [&](void *ptr) { this->DestroyFactory(ptr); });
}

void InternalLibraryLoader::DestroyFactory(void *factory) {
    dlclose(factory);
}
