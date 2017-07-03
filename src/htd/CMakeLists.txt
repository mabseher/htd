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

set(HTD_VERSION_MAJOR 1)
set(HTD_VERSION_MINOR 2)
set(HTD_VERSION_PATCH 0)
set(HTD_VERSION ${HTD_VERSION_MAJOR}.${HTD_VERSION_MINOR}.${HTD_VERSION_PATCH})

if(HTD_GIT_COMMIT_ID)
    set(HTD_VERSION_STRING "${HTD_VERSION} (GitHub-Commit-ID: ${HTD_GIT_COMMIT_ID})")
else()
    set(HTD_VERSION_STRING "${HTD_VERSION}")
endif(HTD_GIT_COMMIT_ID)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd/AssemblyInfo.cpp.in"
               "${PROJECT_SOURCE_DIR}/src/htd/AssemblyInfo.cpp")

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd/Id.hpp.in"
               "${PROJECT_SOURCE_DIR}/include/htd/Id.hpp")

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd/PreprocessorDefinitions.hpp.in"
               "${PROJECT_SOURCE_DIR}/include/htd/PreprocessorDefinitions.hpp")

set(CMAKE_REQUIRED_INCLUDES "${PROJECT_SOURCE_DIR}/include")

check_include_file_cxx(htd/CompilerDetection.hpp HTD_HAVE_COMPILER_DETECTION)

set(HTD_SOVERSION_INTERFACE 0)
set(HTD_SOVERSION_REVISION 0)
set(HTD_SOVERSION_AGE 0)
set(HTD_SOVERSION ${HTD_SOVERSION_INTERFACE}.${HTD_SOVERSION_REVISION}.${HTD_SOVERSION_AGE})

file(GLOB_RECURSE HTD_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd/*.hpp)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

    if(HTD_SHARED_LIBRARY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    endif(HTD_SHARED_LIBRARY)
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif(APPLE)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. SRC_LIST)

add_library(htd ${SRC_LIST} ${HTD_HEADER_LIST})

set_property(TARGET htd PROPERTY CXX_STANDARD 11)
set_property(TARGET htd PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd PROPERTIES VERSION ${HTD_SOVERSION} SOVERSION ${HTD_SOVERSION_INTERFACE})

if(UNIX)
    set_target_properties(htd
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif(UNIX)

install(TARGETS htd DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd" DESTINATION include)
