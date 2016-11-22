//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_ITEST_HPP
#define R_TYPE_ITEST_HPP

class ITest {
public:
    virtual void Test() = 0;
};

// the types of the class factories
typedef ITest* create_t();
typedef void destroy_t(ITest*);

#endif //R_TYPE_ITEST_HPP
