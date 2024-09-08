cmake_minimum_required(VERSION 3.22.1)

project(PADS
        VERSION 0
        DESCRIPTION "PREPROCESSOR ABSTRACTED DATA STRUCTURES"
        LANGUAGES C
)

set(CMAKE_CXX_FLAGS "-std=c17 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(external)
add_subdirectory(structures)

include(CTest)
enable_testing()
add_subdirectory(test)
