#!/bin/bash -e

cmake -S . -B build --no-warn-unused-cli \
    -D CMAKE_CXX_COMPILER=g++ \
    -D BUILD_TESTING=on

cmake --build build -- -j$(( $(nproc) - 1 ))

find build -maxdepth 1 -name "test_*" -executable -exec ./{} \;