//
// Created by hippolyteb on 11/22/16.
//

#include "testClass.hpp"
#include <iostream>

void testClass::Test() {
    std::cout << "TEST" << std::endl;
}

testClass::~testClass() {
    std::cout << "Destroyed :(" << std::endl;
}

extern "C" DLLEXPORT testClass *create() {
    return new testClass();
}

extern "C" DLLEXPORT void destroy(testClass *p) {
    delete p;
}