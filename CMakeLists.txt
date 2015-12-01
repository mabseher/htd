cmake_minimum_required(VERSION 3.1)

project(htd)

include(CPack)
include(CTest)
include(CheckIncludeFileCXX)
include(WriteCompilerDetectionHeader)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Please choose the type of build. Options are: None Debug Release RelWithDebInfo MinSizeRel."
       FORCE )
endif()

subdirs(src/htd)

subdirs(test)
