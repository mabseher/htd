#!/usr/bin/env bash

set -evx
env | sort

mkdir build || true
mkdir build/${HTD_TARGET} || true
cd build/${HTD_TARGET}

if [[ "$RUN_COVERAGE_TEST" == "1" ]]; then
    CXX_FLAGS="${CXX_FLAGS} --coverage"
fi

cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
      -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
      -DHTD_USE_EXTENDED_IDENTIFIERS=${HTD_USE_EXTENDED_IDENTIFIERS} \
      -DHTD_BUILD_TESTS=True \
      -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
      ../..

make VERBOSE=1
make test
