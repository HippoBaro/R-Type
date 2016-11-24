//
// Created by hippolyteb on 11/22/16.
//

#include "InternalLinuxLibraryLoader.hpp"

ExternalClassFactory InternalLibraryLoader::GetFactoryForClass(std::string libraryPath) {
    // load the triangle library
    void *factory = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!factory) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return ExternalClassFactory();
    }

    create_t *create_triangle = (create_t*) dlsym(factory, "create");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return ExternalClassFactory();
    }

    destroy_t* destroy_triangle = (destroy_t*) dlsym(factory, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return ExternalClassFactory();
    }
    return ExternalClassFactory(create_triangle, destroy_triangle);
}

InternalLibraryLoader::InternalLibraryLoader() {}

InternalLibraryLoader::~InternalLibraryLoader() { }
