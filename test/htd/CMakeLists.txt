enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/include")

include_directories("${GTEST_INCLUDE_DIR}")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif(UNIX)

file(GLOB_RECURSE HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.hpp)

set(LIBRARIES ${LIBRARIES} htd gtest gtest_main)

file(GLOB TEST_PROGRAMS "*.cpp")

foreach(TEST_PROGRAM ${TEST_PROGRAMS})
    get_filename_component(TEST_NAME ${TEST_PROGRAM} NAME_WE)

    add_executable(${TEST_NAME} "${TEST_PROGRAM}" ${HEADER_LIST} ${GTEST_INCLUDE_DIR})

    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_link_libraries(${TEST_NAME} htd gtest gtest_main)

    add_test(NAME "${TEST_NAME}" COMMAND "$<TARGET_FILE:${TEST_NAME}>")

    if(MSVC)
        add_custom_command(TARGET ${TEST_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>/"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${TEST_NAME}>" "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>/")
    endif(MSVC)
endforeach()
