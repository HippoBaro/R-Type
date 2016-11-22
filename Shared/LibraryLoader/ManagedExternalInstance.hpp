//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
#define R_TYPE_MANAGEDEXTERNALINSTANCE_HPP

#include <ostream>
#include "ExternalClassFactoryLoader.hpp"
#include "ExternalClassFactory.hpp"

template <class Type>
class ManagedExternalInstance {
private:
    Type *_externalInstance;
    ExternalClassFactory _factory;

public:
    ManagedExternalInstance(const ExternalClassFactory  &factory) : _factory(factory) {
        _externalInstance = (Type *)_factory.getCreate()();
    }

    virtual ~ManagedExternalInstance() {
        if (_externalInstance != nullptr)
            _factory.getDestroy()(_externalInstance);
    }

    Type *
    operator->() const noexcept
    {
        return _externalInstance;
    }
};

#endif //R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
