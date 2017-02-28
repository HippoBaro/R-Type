//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_ILIBRARYLOADER_HPP
#define R_TYPE_ILIBRARYLOADER_HPP

#include <string>
#include "ExternalClassFactory.hpp"

class IInternalLibraryLoader {
public:
	virtual ~IInternalLibraryLoader() {};

	virtual std::shared_ptr<ExternalClassFactory> GetFactoryForClass(std::string libraryPath, std::string const &libName, std::string const &constructor = "create", std::string const &destructor = "destroy") = 0;
	virtual void DestroyFactory(void *) = 0;
};

// the types of the class factories
typedef void* create_t(std::initializer_list<void *>);
typedef void destroy_t(void*);

#endif //R_TYPE_ILIBRARYLOADER_HPP
