cmake_minimum_required(VERSION 2.6.2)

add_library(Test SHARED testClass.cpp ../../Shared/Libs/Interfaces/ITest.hpp)
link_libraries(Test RTypeShared)