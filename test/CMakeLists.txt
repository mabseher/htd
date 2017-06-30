if(BUILD_TESTING)
    enable_testing()

    set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/test/googletest/googletest-release-1.8.0")

    set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/googletest/include")

    add_subdirectory("${GTEST_ROOT}")

    add_subdirectory("${PROJECT_SOURCE_DIR}/test/htd")

    add_dependencies(gtest htd)
endif()
