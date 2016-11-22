//
// Created by hippolyteb on 11/22/16.
//

#include <iostream>
#include <dlfcn.h>
#include "IInternalLibraryLoader.hpp"

class InternalLibraryLoader : public IInternalLibraryLoader {
public:
    ExternalClassFactory GetFactoryForClass(std::string libraryPath) override final;
};
