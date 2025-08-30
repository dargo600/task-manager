#!/bin/bash
#
rm -rf build
mkdir build
cd build
cp -r ../res .
cmake ../src
make

