enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/include")

include_directories("${GTEST_INCLUDE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

file(GLOB_RECURSE HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.hpp)

set(LIBRARIES ${LIBRARIES} htd gtest gtest_main)

file(GLOB TEST_PROGRAMS "*.cpp")

foreach(TEST_PROGRAM ${TEST_PROGRAMS})
    get_filename_component(TEST_NAME ${TEST_PROGRAM} NAME_WE)

    add_executable(${TEST_NAME} "${TEST_PROGRAM}" ${HEADER_LIST} ${GTEST_INCLUDE_DIR})

    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_link_libraries(${TEST_NAME} htd gtest gtest_main)

    add_test("${TEST_NAME}" ${TEST_NAME})
endforeach()
