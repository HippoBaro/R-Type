//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_EXTERNALCLASSFACTORY_HPP
#define R_TYPE_EXTERNALCLASSFACTORY_HPP

#include <functional>
#include <memory>
#include <IService.hpp>

class ExternalClassFactory {
private:
    std::function<void *(std::initializer_list<void *>)> _create = nullptr;
    std::function<void(void *)> _destroy = nullptr;
    std::shared_ptr<void> _libRef = nullptr;
    std::string _libName = std::string();
    std::function<void(void *)> _factoryDestroy = nullptr;

public:
    ExternalClassFactory(const std::function<void *(std::initializer_list<void *>)> &create,
                         const std::function<void(void *)> &_destroy,
                         void *libRef, std::string const &libName,
                         std::function<void(void *)> const &factoryDestroy) :
            _create(create),
            _destroy(_destroy),
            _libRef(std::shared_ptr<void>(libRef, [](void*){})),
            _libName(libName),
            _factoryDestroy(factoryDestroy) {}

    ExternalClassFactory(ExternalClassFactory const &ref) : _create(ref._create), _destroy(ref._destroy), _libRef(ref._libRef), _libName(ref._libName), _factoryDestroy(ref._factoryDestroy) {

    }

    ExternalClassFactory &operator=(ExternalClassFactory const &ref) {
        this->_create = ref._create;
        this->_destroy = ref._destroy;
        this->_libRef = ref._libRef;
        this->_libName = ref._libName;
        this->_factoryDestroy = ref._factoryDestroy;
        return *this;
    }

    void Destroy() {
        _factoryDestroy(_libRef.get());
    }

    const std::function<void *(std::initializer_list<void *>)> &getCreate() const {
        return _create;
    }

    const std::function<void(void *)> &getDestroy() const {
        return _destroy;
    }

    const std::string &getLibName() const {
        return _libName;
    }
};

#endif //R_TYPE_EXTERNALCLASSFACTORY_HPP
