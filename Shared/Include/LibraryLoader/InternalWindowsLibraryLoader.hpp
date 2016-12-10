//
// Created by hippolyteb on 11/22/16.
//

#include <string>
#include <iostream>
#include "IInternalLibraryLoader.hpp"

class InternalLibraryLoader : public IInternalLibraryLoader {
public:
    ExternalClassFactory GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor = "create", std::string const &destructor = "destroy") override final;
    void DestroyFactory(void *pVoid) override final;
};