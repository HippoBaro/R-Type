//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_LIBRARYLOADER_HPP
#define R_TYPE_LIBRARYLOADER_HPP

#include <memory>
#include "ManagedExternalInstance.hpp"
#include "IInternalLibraryLoader.hpp"

#if MSVC
#include "InternalWindowsLibraryLoader.hpp"
#else
#include "InternalLinuxLibraryLoader.hpp"
#endif

class ExternalClassFactoryLoader {
private:
    static std::unique_ptr<IInternalLibraryLoader> _dynLoader;
public:
    template<class Type> static ManagedExternalInstance<Type> GetInstanceOf(std::string libraryPath, std::initializer_list<void *> args, std::string const &constructor = "create", std::string const &destructor = "destroy") {
        return ManagedExternalInstance<Type>(_dynLoader->GetFactoryForClass(libraryPath, constructor, destructor), args);
    }
};

std::unique_ptr<IInternalLibraryLoader> ExternalClassFactoryLoader::_dynLoader = std::unique_ptr<IInternalLibraryLoader>(new InternalLibraryLoader());

#endif //R_TYPE_LIBRARYLOADER_HPP
