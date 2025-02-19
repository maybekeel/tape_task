#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake .. \
    -D CMAKE_CXX_COMPILER=g++ \
    -D BUILD_TESTING=on
make -j$(( $(nproc) - 1 ))