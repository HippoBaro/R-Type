//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_LIBRARYLOADER_HPP
#define R_TYPE_LIBRARYLOADER_HPP

#include <string>
#include <bits/unique_ptr.h>
#include "InternalLinuxLibraryLoader.hpp"
#include "ManagedExternalInstance.hpp"

class ExternalClassFactoryLoader {
private:
    static std::unique_ptr<InternalLibraryLoader> _dynLoader;
public:
    template<class Type> static ManagedExternalInstance<Type> GetInstanceOf(std::string libraryPath) {
        return ManagedExternalInstance<Type>(_dynLoader->GetFactoryForClass(libraryPath));
    }
};

std::unique_ptr<InternalLibraryLoader> ExternalClassFactoryLoader::_dynLoader = std::unique_ptr<InternalLibraryLoader>(new InternalLibraryLoader());

#endif //R_TYPE_LIBRARYLOADER_HPP
