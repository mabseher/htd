include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. SRC_LIST)

write_compiler_detection_header(
  FILE "${PROJECT_SOURCE_DIR}/include/htd/CompilerDetection.hpp"
  PREFIX HTD
  COMPILERS GNU Clang AppleClang MSVC
  FEATURES cxx_noexcept cxx_override cxx_lambdas
)

if (BUILD_SHARED_LIBS)
    set(HTD_SHARED_LIBRARY ON)
else (BUILD_SHARED_LIBS)
    set(HTD_SHARED_LIBRARY OFF)
endif (BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/cmake/Id.hpp.in" "${PROJECT_SOURCE_DIR}/include/htd/Id.hpp")

configure_file("${PROJECT_SOURCE_DIR}/cmake/PreprocessorDefinitions.hpp.in" "${PROJECT_SOURCE_DIR}/include/htd/PreprocessorDefinitions.hpp")

set(CMAKE_REQUIRED_INCLUDES "${PROJECT_SOURCE_DIR}/include")

check_include_file_cxx(htd/CompilerDetection.hpp HTD_HAVE_COMPILER_DETECTION)

set(HTD_SOVERSION_INTERFACE 0)
set(HTD_SOVERSION_REVISION 0)
set(HTD_SOVERSION_AGE 0)
set(HTD_SOVERSION ${HTD_SOVERSION_INTERFACE}.${HTD_SOVERSION_REVISION}.${HTD_SOVERSION_AGE})

file(GLOB_RECURSE HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_library(htd ${SRC_LIST} ${HEADER_LIST})

set_property(TARGET htd PROPERTY CXX_STANDARD 11)
set_property(TARGET htd PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd PROPERTIES VERSION ${HTD_SOVERSION} SOVERSION ${HTD_SOVERSION_INTERFACE})

set_target_properties(htd
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -fvisibility=hidden -Dhtd_EXPORTS")
endif(UNIX)

install(TARGETS htd DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd" DESTINATION include)

if(BUILD_TESTING)
    if(MSVC)
        add_custom_command(
            OUTPUT "${CMAKE_BINARY_DIR}/tests/htd"
            DEPENDS "$<TARGET_FILE:htd>"
            COMMAND ${CMAKE_COMMAND} -E make_directory to_native_path("${CMAKE_BINARY_DIR}/tests/")
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:htd>" to_native_path("${CMAKE_BINARY_DIR}/tests/$<TARGET_FILE_NAME:htd>")
            COMMENT "Copy htd library to directory 'tests' ...")
    endif(MSVC)
endif(BUILD_TESTING)
