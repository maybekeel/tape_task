#!/bin/bash

cmake -S . -B build \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=on \
    -D BUILD_TESTING=off

cmake --build build -- -j$(( $(nproc) - 1 ))