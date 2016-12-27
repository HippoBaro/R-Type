//
// Created by hippolyteb on 12/7/16.
//

#include <LibraryLoader/ExternalClassFactoryLoader.hpp>

std::unique_ptr<ExternalClassFactoryLoader> ExternalClassFactoryLoader::Instance = std::unique_ptr<ExternalClassFactoryLoader>(new ExternalClassFactoryLoader());

ExternalClassFactoryLoader::~ExternalClassFactoryLoader() {
    for (auto &i : _factories) // access by const reference
        i->Destroy();
}