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
    std::shared_ptr<Type> _externalInstance = nullptr;
    ExternalClassFactory _factory;

public:
    ManagedExternalInstance(const ExternalClassFactory &factory, std::initializer_list<void *> &args) : _factory(factory) {
        _externalInstance = std::shared_ptr<Type>((Type *)_factory.getCreate()(args), _factory.getDestroy());
    }

    ManagedExternalInstance(ManagedExternalInstance const &ref) : _factory() {
        this->_externalInstance = ref._externalInstance;
        this->_factory = ref._factory;
    }

    ManagedExternalInstance & operator = (ManagedExternalInstance const &ref){
        this->_externalInstance = ref._externalInstance;
        this->_factory = ref._factory;
        return *this;
    };

    virtual ~ManagedExternalInstance() { }

    Type *GetInstance() const noexcept {
        return _externalInstance.get();
    }

    Type *operator->() const noexcept  {
        return _externalInstance.get();
    }
};

#endif //R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
