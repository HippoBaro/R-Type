//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_LIBRARYLOADER_HPP
#define R_TYPE_LIBRARYLOADER_HPP

#include <memory>
#include <vector>
#include "ManagedExternalInstance.hpp"
#include "IInternalLibraryLoader.hpp"

#if MSVC
#include "InternalWindowsLibraryLoader.hpp"
#else
#include "InternalLinuxLibraryLoader.hpp"
#endif

class ExternalClassFactoryLoader {
private:
    std::unique_ptr<IInternalLibraryLoader> _dynLoader = std::unique_ptr<IInternalLibraryLoader>(new InternalLibraryLoader());
    std::vector<std::shared_ptr<ExternalClassFactory>> _factories = std::vector<std::shared_ptr<ExternalClassFactory>>();

private:
    std::shared_ptr<ExternalClassFactory> GetFactoryOf(std::string const &libraryPath, std::string const &libName, std::string const &constructor, std::string const &destructor) {
        for (const auto &i : _factories) // access by const reference
            if (i->getLibName() == libName)
                return i;
        std::cout << "Loading " << libraryPath << libName << " symbols" << std::endl;
        auto newRef = _dynLoader->GetFactoryForClass(libraryPath, libName, constructor, destructor);
        _factories.push_back(newRef);
        return newRef;
    }

public:
    template<class Type> std::shared_ptr<ManagedExternalInstance<Type>> GetInstanceOf(std::string libraryPath, std::string const &libName, std::initializer_list<void *> args, std::string const &constructor = "create", std::string const &destructor = "destroy") {
        return std::make_shared<ManagedExternalInstance<Type>>(GetFactoryOf(libraryPath, libName, constructor, destructor), args);
    }

    virtual ~ExternalClassFactoryLoader();

public:
    static std::unique_ptr<ExternalClassFactoryLoader> Instance;
};

#endif //R_TYPE_LIBRARYLOADER_HPP
