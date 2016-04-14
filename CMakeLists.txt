cmake_minimum_required(VERSION 3.2)

project(htd)

set(CPACK_GENERATOR "STGZ;TGZ;TZ;ZIP")
set(CPACK_SOURCE_GENERATOR "STGZ;TGZ;TZ;ZIP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A small but efficient C++ library for computing (customized) tree and hypertree decompositions.")
set(CPACK_PACKAGE_VENDOR "Michael Abseher (abseher@dbai.tuwien.ac.at)")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "9")
set(CPACK_PACKAGE_VERSION_PATCH "0")

include(CPack)
include(CTest)
include(CheckIncludeFileCXX)
include(WriteCompilerDetectionHeader)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Please choose the type of build. Options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE )
endif()

if (NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif()

if (DEFINED HTD_DEBUG_OUTPUT)
    if (HTD_DEBUG_OUTPUT)
        message("Debugging output is enabled!")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHTD_DEBUG_OUTPUT" )
    endif()
endif()

if (DEFINED HTD_USE_EXTENDED_IDENTIFIERS)
    if (HTD_USE_EXTENDED_IDENTIFIERS)
        message("Extended identifiers will be used!")

        set(HTD_ID_TYPE "std::size_t" )
    else()
        set(HTD_ID_TYPE "std::uint_least32_t" )
    endif()
else()
    set(HTD_ID_TYPE "std::uint_least32_t" )
endif()

if (NOT DEFINED HTD_BUILD_TESTS)
    message("Tests are disabled!")

    set(HTD_BUILD_TESTS OFF)
endif()

subdirs(src/htd)

subdirs(test)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
