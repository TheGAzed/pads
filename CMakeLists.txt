cmake_minimum_required(VERSION 3.22.1)

project(PREPROCESSOR_ABSTRACTED_DATA_STRUCTURES
        VERSION 0
        DESCRIPTION "PREPROCESSOR ABSTRACTED DATA STRUCTURES"
        LANGUAGES C
)

if (MSVC)
    add_compile_options(/W2 /WX /Zi)
else ()
    add_compile_options(-std=c99 -O0 -g -Wall -Wextra -Wconversion -Werror)
endif ()

add_subdirectory(external)

add_library(PADS INTERFACE)
target_include_directories(PADS INTERFACE source)
set_target_properties(PADS PROPERTIES LINKER_LANGUAGE C)

include(CTest)
enable_testing()

add_subdirectory(test)

if (EXISTS "${CMAKE_SOURCE_DIR}/experiment")
    add_subdirectory(experiment)
endif ()
