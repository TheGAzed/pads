cmake_minimum_required(VERSION 3.22.1)

project(PADS
        VERSION 0
        DESCRIPTION "PREPROCESSOR ABSTRACTED DATA STRUCTURES"
        LANGUAGES C
)

set(CMAKE_CXX_FLAGS "-std=c11 -Wall -Wextra -Werror -pedantic -Wconversion")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(external)

add_library(project_headers INTERFACE)
target_include_directories(project_headers INTERFACE source)
set_target_properties(project_headers PROPERTIES LINKER_LANGUAGE C)

include(CTest)
enable_testing()
add_subdirectory(source)
