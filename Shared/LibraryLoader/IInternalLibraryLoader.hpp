//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_ILIBRARYLOADER_HPP
#define R_TYPE_ILIBRARYLOADER_HPP

#include <string>
#include "../../Shared/LibraryLoader/ExternalClassFactory.hpp"

class IInternalLibraryLoader {
public:
	virtual ExternalClassFactory GetFactoryForClass(std::string libraryPath) = 0;
};

// the types of the class factories
typedef void* create_t();
typedef void destroy_t(void*);

#endif //R_TYPE_ILIBRARYLOADER_HPP
