#!/usr/bin/env sh

set -evx
env | sort

mkdir build || true
mkdir build/$HTD_TARGET || true
cd build/$HTD_TARGET

cmake -DCMAKE_BUILD_TYPE=Debug \
      -DHTD_BUILD_TESTS=True \
      -DCMAKE_CXX_FLAGS=$CXX_FLAGS \
      ../../$HTD_TARGET

make
#make test
