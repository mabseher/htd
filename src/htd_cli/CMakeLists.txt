include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(. HTD_CLI_SRC_LIST)

list(REMOVE_ITEM HTD_CLI_SRC_LIST "main.cpp")

set(HTD_CLI_SOVERSION_INTERFACE 0)
set(HTD_CLI_SOVERSION_REVISION 0)
set(HTD_CLI_SOVERSION_AGE 0)
set(HTD_CLI_SOVERSION ${HTD_CLI_SOVERSION_INTERFACE}.${HTD_CLI_SOVERSION_REVISION}.${HTD_CLI_SOVERSION_AGE})

add_library(htd_cli ${HTD_CLI_SRC_LIST} ${HEADER_LIST})

set_property(TARGET htd_cli PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_cli PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET htd_cli PROPERTY POSITION_INDEPENDENT_CODE 1)

set_target_properties(htd_cli PROPERTIES VERSION ${HTD_CLI_SOVERSION} SOVERSION ${HTD_CLI_SOVERSION_INTERFACE})

set_target_properties(htd_cli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS htd_cli DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd_cli" DESTINATION include)

set(HTD_MAIN_VERSION_MAJOR 0)
set(HTD_MAIN_VERSION_MINOR 9)
set(HTD_MAIN_VERSION_PATCH 9)
set(HTD_MAIN_VERSION ${HTD_MAIN_VERSION_MAJOR}.${HTD_MAIN_VERSION_MINOR}.${HTD_MAIN_VERSION_PATCH} )

add_executable(htd_main "main.cpp")

set_property(TARGET htd_main PROPERTY CXX_STANDARD 11)
set_property(TARGET htd_main PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(htd_main PROPERTIES VERSION ${HTD_MAIN_VERSION})

set_target_properties(htd_main
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (UNIX)
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
endif(UNIX)

target_link_libraries(htd_main htd htd_cli)

install(TARGETS htd_main DESTINATION bin)
