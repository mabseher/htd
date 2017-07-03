include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. HTD_MAIN_SRC_LIST)

set(HTD_MAIN_VERSION_MAJOR 1)
set(HTD_MAIN_VERSION_MINOR 2)
set(HTD_MAIN_VERSION_PATCH 0)
set(HTD_MAIN_VERSION ${HTD_MAIN_VERSION_MAJOR}.${HTD_MAIN_VERSION_MINOR}.${HTD_MAIN_VERSION_PATCH})

file(GLOB_RECURSE HTD_MAIN_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd_main/*.hpp)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif(APPLE)

add_executable(htd_main ${HTD_MAIN_SRC_LIST} ${HTD_MAIN_HEADER_LIST})

set_property(TARGET htd_main PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_main PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(htd_main PROPERTIES VERSION ${HTD_MAIN_VERSION})

if(UNIX)
    set_target_properties(htd_main
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_exhaustive.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_exhaustive.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_exhaustive_minfill.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_exhaustive_minfill.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_exhaustive_mindegree.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_exhaustive_mindegree.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/pace16_build_test.sh"
                   "${CMAKE_BINARY_DIR}/bin/pace16_build_test.sh" COPYONLY)
endif(UNIX)

target_link_libraries(htd_main htd htd_io htd_cli)

install(TARGETS htd_main DESTINATION bin)
