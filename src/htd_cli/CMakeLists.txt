include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. HTD_CLI_SRC_LIST)

list(REMOVE_ITEM HTD_CLI_SRC_LIST "main.cpp")

if (BUILD_SHARED_LIBS)
    set(HTD_CLI_SHARED_LIBRARY ON)
else (BUILD_SHARED_LIBS)
    set(HTD_CLI_SHARED_LIBRARY OFF)
endif (BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd_cli/PreprocessorDefinitions.hpp.in"
               "${PROJECT_SOURCE_DIR}/include/htd_cli/PreprocessorDefinitions.hpp")

set(HTD_CLI_SOVERSION_INTERFACE 0)
set(HTD_CLI_SOVERSION_REVISION 0)
set(HTD_CLI_SOVERSION_AGE 0)
set(HTD_CLI_SOVERSION ${HTD_CLI_SOVERSION_INTERFACE}.${HTD_CLI_SOVERSION_REVISION}.${HTD_CLI_SOVERSION_AGE})

file(GLOB_RECURSE HTD_CLI_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd_cli/*.hpp)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

    if(HTD_CLI_SHARED_LIBRARY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    endif(HTD_CLI_SHARED_LIBRARY)
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif(APPLE)

add_library(htd_cli ${HTD_CLI_SRC_LIST} ${HTD_CLI_HEADER_LIST})

set_property(TARGET htd_cli PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_cli PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd_cli PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd_cli PROPERTIES VERSION ${HTD_CLI_SOVERSION} SOVERSION ${HTD_CLI_SOVERSION_INTERFACE})

if(UNIX)
    set_target_properties(htd_cli
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif(UNIX)

install(TARGETS htd_cli DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd_cli" DESTINATION include)
