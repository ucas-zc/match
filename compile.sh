#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=GTEST -DCMAKE_BUILD_RPATH=/opt/ide ..
#$make gen_coverage_html
make
