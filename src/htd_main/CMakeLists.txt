include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. HTD_MAIN_SRC_LIST)

set(HTD_MAIN_VERSION_MAJOR 0)
set(HTD_MAIN_VERSION_MINOR 9)
set(HTD_MAIN_VERSION_PATCH 9)
set(HTD_MAIN_VERSION ${HTD_MAIN_VERSION_MAJOR}.${HTD_MAIN_VERSION_MINOR}.${HTD_MAIN_VERSION_PATCH} )

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif(UNIX)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

add_executable(htd_main ${HTD_MAIN_SRC_LIST} ${HEADER_LIST})

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
endif(UNIX)

if(UNIX)
    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_minfill_exhaustive.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_minfill_exhaustive.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_minfill_iterative_100_20.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_minfill_iterative_100_20.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_minfill_iterative_256_64.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_minfill_iterative_256_64.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_mindegree_exhaustive.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_mindegree_exhaustive.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_mindegree_iterative_100_20.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_mindegree_iterative_100_20.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/htd_gr2td_mindegree_iterative_256_64.sh"
                   "${CMAKE_BINARY_DIR}/bin/htd_gr2td_mindegree_iterative_256_64.sh" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/scripts/pace16_build_test.sh"
                   "${CMAKE_BINARY_DIR}/bin/pace16_build_test.sh" COPYONLY)
endif(UNIX)

target_link_libraries(htd_main htd htd_cli)

install(TARGETS htd_main DESTINATION bin)
