include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. HTD_IO_SRC_LIST)

if (BUILD_SHARED_LIBS)
    set(HTD_IO_SHARED_LIBRARY ON)
else (BUILD_SHARED_LIBS)
    set(HTD_IO_SHARED_LIBRARY OFF)
endif (BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd_io/PreprocessorDefinitions.hpp.in"
               "${PROJECT_SOURCE_DIR}/include/htd_io/PreprocessorDefinitions.hpp")

set(HTD_IO_SOVERSION_INTERFACE 0)
set(HTD_IO_SOVERSION_REVISION 0)
set(HTD_IO_SOVERSION_AGE 0)
set(HTD_IO_SOVERSION ${HTD_IO_SOVERSION_INTERFACE}.${HTD_IO_SOVERSION_REVISION}.${HTD_IO_SOVERSION_AGE})

file(GLOB_RECURSE HTD_IO_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd_io/*.hpp)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

    if(HTD_IO_SHARED_LIBRARY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    endif(HTD_IO_SHARED_LIBRARY)
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

add_library(htd_io ${HTD_IO_SRC_LIST} ${HTD_IO_HEADER_LIST})

set_property(TARGET htd_io PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_io PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd_io PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd_io PROPERTIES VERSION ${HTD_IO_SOVERSION} SOVERSION ${HTD_IO_SOVERSION_INTERFACE})

if(UNIX)
    set_target_properties(htd_io
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif(UNIX)

if(MSVC)
    target_link_libraries(htd_io htd)
endif(MSVC)

install(TARGETS htd_io DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd_io" DESTINATION include)
