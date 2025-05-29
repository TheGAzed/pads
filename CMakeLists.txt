cmake_minimum_required(VERSION 3.22.1)

project(PADS VERSION 1)

add_subdirectory(external)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE source)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

if (NOT DEFINED IS_PADS_TESTING)
    set(IS_PADS_TESTING TRUE)
endif ()

if (IS_PADS_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)

    if (EXISTS "${CMAKE_SOURCE_DIR}/experiment")
        add_subdirectory(experiment)
    endif ()
endif ()
