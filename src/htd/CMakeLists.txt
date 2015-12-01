include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. SRC_LIST)

write_compiler_detection_header(
  FILE "${PROJECT_SOURCE_DIR}/include/htd/CompilerDetection.hpp"
  PREFIX HTD
  COMPILERS GNU Clang
  FEATURES cxx_override
)

set(CMAKE_REQUIRED_INCLUDES "${PROJECT_SOURCE_DIR}/include")

check_include_file_cxx(htd/CompilerDetection.hpp HTD_HAVE_COMPILER_DETECTION)

set(HTD_VERSION_MAJOR 0)
set(HTD_VERSION_MINOR 1)
set(HTD_VERSION_PATCH 0)
set(HTD_VERSION ${HTD_VERSION_MAJOR}.${HTD_VERSION_MINOR}.${HTD_VERSION_PATCH} )

file(GLOB_RECURSE HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_library(htd SHARED ${SRC_LIST} ${HEADER_LIST})
add_library(htd_static STATIC ${SRC_LIST} ${HEADER_LIST})

set_property(TARGET htd PROPERTY CXX_STANDARD 11)
set_property(TARGET htd PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd_static PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_static PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd PROPERTIES VERSION ${HTD_VERSION} SOVERSION ${HTD_VERSION_MAJOR})

set_target_properties(htd_static PROPERTIES VERSION ${HTD_VERSION} SOVERSION ${HTD_VERSION_MAJOR})

set_target_properties(htd htd_static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
