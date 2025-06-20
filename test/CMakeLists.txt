if (MSVC)
    add_compile_options(/W2 /WX /Zi)
else ()
    add_compile_options(-std=c99 -O0 -g -Wall -Wextra -Wconversion -Werror -Wpedantic)
endif ()

add_library(functions helper/functions.c)
target_include_directories(functions PUBLIC .)

add_subdirectory(sequence)
add_subdirectory(list)
add_subdirectory(set)
add_subdirectory(priority)
#add_subdirectory(matrix_graph/tests)
