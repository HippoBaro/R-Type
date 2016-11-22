//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_TESTCLASS_HPP
#define R_TYPE_TESTCLASS_HPP

#include "../../Shared/Libs/Interfaces/ITest.hpp"

class testClass : public ITest {
public:
    virtual void Test();
    virtual ~testClass();
};

#endif //R_TYPE_TESTCLASS_HPP
