#!/bin/bash

echo "Updating packages"
sudo apt-get update
echo "Installing dependencies"
sudo apt-get install gcc-5 g++-5 cmake
export CXX="g++-5" CC="gcc-5"
echo "Building project"
mkdir build && cd build
cmake -D RTYPE_BUILD_SERVER_ONLY=1 ..
make
echo "Killing current server instance if any"
sudo pkill -f R_Type_Server
echo "Launching"
./R_Type_Server