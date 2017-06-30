enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/include")

include_directories("${GTEST_INCLUDE_DIR}")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif(APPLE)

file(GLOB_RECURSE HTD_FULL_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.hpp)

set(LIBRARIES ${LIBRARIES} htd gtest gtest_main)

file(GLOB TEST_PROGRAMS "*.cpp")

foreach(TEST_PROGRAM ${TEST_PROGRAMS})
    get_filename_component(TEST_NAME ${TEST_PROGRAM} NAME_WE)

    add_executable(${TEST_NAME} "${TEST_PROGRAM}" ${HTD_FULL_HEADER_LIST} ${GTEST_INCLUDE_DIR})

    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_link_libraries(${TEST_NAME} htd gtest gtest_main)

    add_test(NAME "${TEST_NAME}" COMMAND "$<TARGET_FILE:${TEST_NAME}>")
endforeach()
