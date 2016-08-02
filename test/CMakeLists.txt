if (BUILD_TESTING)
    enable_testing()

    set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/test/googletest/googletest-release-1.7.0")

    set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")

    add_subdirectory("${GTEST_ROOT}")

    add_subdirectory("${PROJECT_SOURCE_DIR}/test/htd")

    set_target_properties(gtest
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )

    set_target_properties(gtest_main
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )
endif()
