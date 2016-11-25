//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
#define R_TYPE_MANAGEDEXTERNALINSTANCE_HPP

#include <ostream>
#include "ExternalClassFactory.hpp"

template <class Type>
class ManagedExternalInstance {
private:
    Type *_externalInstance = nullptr;
    ExternalClassFactory _factory;

public:
    ManagedExternalInstance(const ExternalClassFactory  &factory) : _factory(factory) {
        _externalInstance = (Type *)_factory.getCreate()(nullptr);
    }

    ManagedExternalInstance(ManagedExternalInstance const &) = default;
    ManagedExternalInstance & operator = (ManagedExternalInstance const &) = default;

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
