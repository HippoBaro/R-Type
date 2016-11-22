//
// Created by hippolyteb on 11/22/16.
//

#include "testClass.hpp"

void testClass::Test() {
    std::cout << "TEST" << std::endl;
}

testClass::~testClass() {
    std::cout << "Destroyed :(" << std::endl;
}

extern "C" testClass* create() {
    return new testClass();
}

extern "C" void destroy(testClass* p) {
    delete p;
}