#!/bin/bash

set -e
touch CMakeLists.txt
mkdir -p .build_release
rm -f .build_release/CMakeCache.txt

(
cd .build_release
cmake -DCMAKE_CXX_COMPILER=clang++ ..
make all
)

exec .build_release/main

