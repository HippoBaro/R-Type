#!/bin/bash

echo "Updating packages"
sudo apt-get update
echo "Installing dependencies"
sudo apt-get install gcc-5 g++-5 cmake
echo "Building project"
mkdir build && cd build
cmake -D RTYPE_BUILD_SERVER_ONLY=1 ..
make
echo "Launching"
./R_Type_Server