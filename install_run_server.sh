#!/bin/bash

sudo apt-get update
sudo apt-get install gcc-5 g++-5 cmake
mkdir build && cd build && cmake ..
make
./R_Type_Server