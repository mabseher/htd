#!/usr/bin/env bash

set -evx
env | grep -v "COVERALLS" | sort

mkdir build || true
mkdir build/${HTD_TARGET} || true
cd build/${HTD_TARGET}

if [[ "$RUN_COVERAGE_TEST" == "1" ]]; then
    CXX_FLAGS="${CXX_FLAGS} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors -Wno-invalid-offsetof -O0"
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
          -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
          -DHTD_USE_EXTENDED_IDENTIFIERS=${HTD_USE_EXTENDED_IDENTIFIERS} \
          -DCMAKE_OSX_ARCHITECTURES=x86_64 \
          -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
          ../..
else
    cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
          -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
          -DHTD_USE_EXTENDED_IDENTIFIERS=${HTD_USE_EXTENDED_IDENTIFIERS} \
          -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
          ../..
fi

make VERBOSE=1

if [[ "$RUN_COVERAGE_TEST" == "1" ]]; then
    lcov --directory .. --base-directory ../.. --zerocounters
    lcov --directory .. --base-directory ../.. --capture --initial --output-file coverage.info
fi

make test