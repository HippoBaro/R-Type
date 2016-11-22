//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_ILIBRARYLOADER_HPP
#define R_TYPE_ILIBRARYLOADER_HPP

#ifndef MSVC
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#include "../../Shared/LibraryLoader/ExternalClassFactory.hpp"

class IInternalLibraryLoader {
public:
	virtual ExternalClassFactory GetFactoryForClass(std::string libraryPath) = 0;
};

// the types of the class factories
typedef void* create_t();
typedef void destroy_t(void*);

#endif //R_TYPE_ILIBRARYLOADER_HPP
