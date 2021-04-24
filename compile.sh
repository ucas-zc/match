#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=SHARED -DCMAKE_BUILD_RPATH=/opt/ide ..
make
cmake -DCMAKE_BUILD_TYPE=STATIC -DCMAKE_BUILD_RPATH=/opt/ide ..
make
