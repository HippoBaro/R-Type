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

public:
    ExternalClassFactory() {}

    ExternalClassFactory(const std::function<void *(std::initializer_list<void *>)> &create, const std::function<void(void *)> &_destroy) : _create(create), _destroy(_destroy) { }

    const std::function<void *(std::initializer_list<void *>)> &getCreate() const {
        return _create;
    }

    const std::function<void(void *)> &getDestroy() const {
        return _destroy;
    }
};

#endif //R_TYPE_EXTERNALCLASSFACTORY_HPP
