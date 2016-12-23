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


    ManagedExternalInstance() : _factory() { }

    ManagedExternalInstance(ManagedExternalInstance const &ref) : _externalInstance(ref._externalInstance), _factory(ref._factory) { }

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

    bool operator==(const ManagedExternalInstance &rhs) const {
        return std::tie(_externalInstance, _factory) == std::tie(rhs._externalInstance, rhs._factory);
    }

    bool operator!=(const ManagedExternalInstance &rhs) const {
        return !(rhs == *this);
    }
};

#endif //R_TYPE_MANAGEDEXTERNALINSTANCE_HPP
