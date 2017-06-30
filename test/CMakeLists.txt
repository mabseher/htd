if(BUILD_TESTING)
    enable_testing()

    set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/test/googletest/googletest-release-1.8.0")

    set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/googletest/include")

    add_subdirectory("${GTEST_ROOT}")

    add_subdirectory("${PROJECT_SOURCE_DIR}/test/htd")

    set(gtest_hide_internal_symbols ON CACHE INTERNAL "Build gtest with internal symbols hidden in shared libraries.")

    add_dependencies(gtest htd)
endif()
