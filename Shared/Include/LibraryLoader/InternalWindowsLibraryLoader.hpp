//
// Created by hippolyteb on 11/22/16.
//

#include <string>
#include <iostream>
#include "IInternalLibraryLoader.hpp"

class InternalLibraryLoader : public IInternalLibraryLoader {
public:
    std::shared_ptr<ExternalClassFactory> GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor = "create", std::string const &destructor = "destroy") override final;
    void DestroyFactory(void *pVoid) override final;
};
