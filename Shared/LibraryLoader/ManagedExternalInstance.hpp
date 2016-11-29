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
    bool _hasBeenCopied = false;

public:
    ManagedExternalInstance(const ExternalClassFactory &factory, std::initializer_list<void *> &args) : _factory(factory) {
        _externalInstance = (Type *)_factory.getCreate()(args);
    }

    ManagedExternalInstance(ManagedExternalInstance &ref){
        ref._hasBeenCopied = true;
        this->_externalInstance = ref._externalInstance;
        this->_factory = ref._factory;
    }

    ManagedExternalInstance(ManagedExternalInstance const &ref){ }

    virtual ~ManagedExternalInstance() {
        if (_externalInstance != nullptr && _hasBeenCopied)
            _factory.getDestroy()(_externalInstance);
    }

    Type *GetInstance() const noexcept {
        return _externalInstance;
    }

    Type *operator->() const noexcept  {
        return _externalInstance;
    }
};

#endif //R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
