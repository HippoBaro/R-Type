//
// Created by hippolyteb on 11/20/16.
//

#include <iostream>
#include <dlfcn.h>
#include "../../Shared/Interfaces/ITest.hpp"

int main() {
    using std::cout;
    using std::cerr;

    // load the triangle library
    void* triangle = dlopen("/home/hippolyteb/.CLion2016.2/system/cmake/generated/R-Type-32b3c3e3/32b3c3e3/Debug2/SharedLibs/Test/libTest.so", RTLD_LAZY);
    if (!triangle) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();

    // load the symbols
    create_t* create_triangle = (create_t*) dlsym(triangle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return 1;
    }

    destroy_t* destroy_triangle = (destroy_t*) dlsym(triangle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return 1;
    }

    // create an instance of the class
    ITest* poly = create_triangle();

    // use the class
    poly->Test();

    // destroy the class
    destroy_triangle(poly);

    // unload the triangle library
    dlclose(triangle);
}